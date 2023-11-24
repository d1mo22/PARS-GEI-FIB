# Made by a FIBER
# This program will play different matches with random seeds to allow
# you to test your program multiple times at once
#
# You may need to install ($pip3 install subprocess)
# To run it ($python3 multiple_games.py)

from subprocess import Popen, PIPE
import random
import os

def main():
    n_games = input("How many games do you want to play: ")
    p1 = input("Name of the player1: ")
    p2 = input("Name of the player2: ")
    p3 = input("Name of the player3: ")
    p4 = input("Name of the player4: ")
    info = input("Do you want to diplay the number of games played? [y/n]: ")
    victories = {p1:0, p2:0, p3:0, p4:0}
    classifications = {p1:0, p2:0, p3:0, p4:0}
    eliminations = {p1:0, p2:0, p3:0, p4:0}
    print("\nPlaying... (this process might take some time)\n")
    for i in range(0, int(n_games)):
        n_random = random.randint(0, 100000000)
        nom_sortida = str(n_random)+".out"
        if(info == "y"): print("Playing " + str(i+1) + " of " + n_games + " games (seed: " + str(n_random) + ")")
        process = Popen(["./Game", p1, p2, p3, p4, "-s", str(n_random), "-i", "default.cnf", "-o", nom_sortida], stderr=PIPE)
        stderr = process.communicate()
        r = str(stderr).split()
        score1 = r[len(r)-23]
        score1 = int(score1[:len(score1) - 7])
        score2 = r[len(r)-18]
        score2 = int(score2[:len(score2) - 7])
        score3 = r[len(r)-13]
        score3 = int(score3[:len(score3) - 7])
        score4 = r[len(r)-8]
        score4 = int(score4[:len(score4) - 7])
        if score1 > score3 and score1 > score4 and score2 > score3 and score2 > score4:
            classifications[p1] += 1
            classifications[p2] += 1
        if score1 > score2 and score1 > score4 and score3 > score2 and score3 > score4:
            classifications[p1] += 1
            classifications[p3] += 1
        if score1 > score2 and score1 > score3 and score4 > score2 and score4 > score3:
            classifications[p1] += 1
            classifications[p4] += 1
        if score2 > score1 and score2 > score4 and score3 > score1 and score3 > score4:
            classifications[p2] += 1
            classifications[p3] += 1
        if score2 > score1 and score2 > score3 and score4 > score1 and score4 > score3:
            classifications[p2] += 1
            classifications[p4] += 1
        if score3 > score1 and score3 > score2 and score4 > score1 and score4 > score2:
            classifications[p3] += 1
            classifications[p4] += 1
        if score1 < score2 and score1 < score3 and score1 < score4: eliminations[p1] += 1
        if score1 > score2 and score2 < score3 and score2 < score4: eliminations[p2] += 1
        if score1 > score3 and score2 > score3 and score3 < score4: eliminations[p3] += 1
        if score1 > score4 and score4 < score2 and score3 > score4: eliminations[p4] += 1
        r = r[len(r)-6]
        victories[r] += 1
        os.remove(os.getcwd()+"/"+nom_sortida)

    print("\n----------------------")
    print("Victory rates:")
    print(p1 + " : " + str(100*(victories[p1]/int(n_games))) + " %")
    print(p2 + " : " + str(100*(victories[p2]/int(n_games))) + " %")
    print(p3 + " : " + str(100*(victories[p3]/int(n_games))) + " %")
    print(p4 + " : " + str(100*(victories[p4]/int(n_games))) + " %")
    print("\nClassification rates:")
    print(p1 + " : " + str(100*(classifications[p1]/int(n_games))) + " %")
    print(p2 + " : " + str(100*(classifications[p2]/int(n_games))) + " %")
    print(p3 + " : " + str(100*(classifications[p3]/int(n_games))) + " %")
    print(p4 + " : " + str(100*(classifications[p4]/int(n_games))) + " %")
    print("\nElimination rates:")
    print(p1 + " : " + str(100*(eliminations[p1]/int(n_games))) + " %")
    print(p2 + " : " + str(100*(eliminations[p2]/int(n_games))) + " %")
    print(p3 + " : " + str(100*(eliminations[p3]/int(n_games))) + " %")
    print(p4 + " : " + str(100*(eliminations[p4]/int(n_games))) + " %")
    print("----------------------\n")

if __name__ == "__main__":
	main()