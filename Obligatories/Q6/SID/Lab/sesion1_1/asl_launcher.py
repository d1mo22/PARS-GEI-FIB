import argparse
import asyncio

from spade_bdi.bdi import BDIAgent


async def main():
    parser = argparse.ArgumentParser(description='spade bdi launcher example')
    parser.add_argument('--login', type=str, default="basicagent", help='your team login.')
    parser.add_argument('--server', type=str, default="localhost", help='XMPP server address.')
    parser.add_argument('--password', type=str, default="bdipassword", help='XMPP password for the agents.')
    parser.add_argument('--asl', type=str, default="default.asl", help='asl file with JASON code.')
    parser.add_argument('--time', type=int, default=1, help='duration time (in seconds) of the execution.')
    args = parser.parse_args()
    a = BDIAgent("Agent_{}@{}".format(args.login, args.server), args.password, args.asl)

    await a.start()
    await asyncio.sleep(args.time)
    await a.stop()


if __name__ == '__main__':
    asyncio.run(main())
