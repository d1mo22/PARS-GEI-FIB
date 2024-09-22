#! /bin/bash
nom="$1"
dir=$(dirname "$0")
if [ ${dir:0:1} != "/" ]; then 
   dir="$PWD/$dir"
fi

if ( ! `grep Copyright $nom >/dev/null` ); then 
    tmpf=$(mktemp -p .)
    cat "$dir"/cpwrt.head "$nom" > $tmpf
    mv $tmpf "$nom"
else
    echo "No need!"
fi
