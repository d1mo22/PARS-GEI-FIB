import argparse
import asyncio

from spade_bdi.bdi import BDIAgent

parser = argparse.ArgumentParser(description='spade bdi basic example')
parser.add_argument('--login', type=str, default="basicagent", help='your team login.')
parser.add_argument('--server', type=str, default="localhost", help='XMPP server address.')
parser.add_argument('--password', type=str, default="bdipassword", help='XMPP password for the agents.')
args = parser.parse_args()
print("fact ", L, " == ", Y)

async def main():
    a = BDIAgent("BasicAgent_{}@{}".format(args.login, args.server), args.password, "basic.asl")
    await a.start()
    await asyncio.sleep(5)

    a.bdi.set_belief("car", "azul", "big")
    a.bdi.print_beliefs()
    print("GETTING FIRST CAR BELIEF")
    print(a.bdi.get_belief("car"))
    a.bdi.print_beliefs()
    a.bdi.remove_belief("car", 'azul', "big")
    a.bdi.print_beliefs()
    print(a.bdi.get_beliefs())
    a.bdi.set_belief("car", 'amarillo')
    await asyncio.sleep(1)
    await a.stop()


if __name__ == '__main__':
    asyncio.run(main())
