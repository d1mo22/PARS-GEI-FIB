import argparse
import os
import re
import logging
from elasticsearch import Elasticsearch
from elasticsearch.helpers import bulk
from elasticsearch.exceptions import NotFoundError
from elasticsearch_dsl import Index

logging.basicConfig(level=logging.INFO, format="%(asctime)s [%(levelname)s] %(message)s")

def generate_files_list(path):
    """Generates a list of all files in a directory tree."""
    return [
        os.path.join(root, f)
        for root, _, files in os.walk(path)
        for f in files if "DS_Store" not in f
    ]

def read_file(filepath):
    """Read file content with fallback encodings."""
    try:
        with open(filepath, "r", encoding="utf-8") as f:
            return re.sub(r"\s+", " ", f.read()).strip()
    except UnicodeDecodeError:
        with open(filepath, "r", encoding="iso-8859-1") as f:
            return re.sub(r"\s+", " ", f.read()).strip()

def main(args):
    client = Elasticsearch(args.host, request_timeout=1000)

    # Define index settings with custom analyzer
    analysis = {
        "analyzer": {
            "default": {
                "type": "custom",
                "tokenizer": args.token,
                "filter": args.filter
            }
        }
    }

    ind = Index(args.index, using=client)

    # Drop index if requested
    if ind.exists():
        if args.force:
            logging.info("Deleting existing index: %s", args.index)
            ind.delete()
        else:
            logging.error("Index %s already exists. Use --force to overwrite.", args.index)
            logging.error("MAKE SURE YOU PUT THE --force FLAG BEFORE --filter")
            return

    # Create index with settings
    ind.settings(number_of_shards=1, analysis=analysis)
    ind.create()

    # Ensure path is not tokenized
    client.indices.put_mapping(
        index=args.index,
        properties={"path": {"type": "keyword"}}
    )

    # Prepare documents
    lfiles = generate_files_list(args.path)
    logging.info("Indexing %d files", len(lfiles))

    lcommands = [
        {"_op_type": "index", "_index": args.index, "_id": i+1, "path": f, "text": read_file(f)}
        for i, f in enumerate(lfiles)
    ]

    # Bulk index
    bulk(client, lcommands)
    client.indices.refresh(index=args.index)
    logging.info("Indexing completed successfully.")

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--path", required=True, help="Path to files")
    parser.add_argument("--index", required=True, help="Index name")
    parser.add_argument("--token", default="standard",
                        choices=["standard", "whitespace", "classic", "letter"],
                        help="Text tokenizer")
    parser.add_argument("--filter", default=["lowercase"], nargs=argparse.REMAINDER,
                        help="Text filters (lowercase, asciifolding, stop, porter_stem, kstem, snowball)")
    parser.add_argument("--host", default="http://localhost:9200", help="Elasticsearch host")
    parser.add_argument("--force", action="store_true", help="Force overwrite of existing index")
    args = parser.parse_args()
    main(args)
