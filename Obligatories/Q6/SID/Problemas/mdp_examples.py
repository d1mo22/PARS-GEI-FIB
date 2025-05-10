import abc
import math
import random
from typing import Any, List, Mapping


####################################
# Abstract class for scenario params
####################################
class Game(abc.ABC):
    @abc.abstractmethod
    def initial_state(self) -> Any:
        pass

    @abc.abstractmethod
    def states(self) -> List[Any]:
        pass

    @abc.abstractmethod
    def actions(self) -> List[Any]:
        pass

    @abc.abstractmethod
    def transitions(self) -> Mapping[Any, Mapping[Any, Mapping[Any, float]]]:
        pass

    @abc.abstractmethod
    def rewards(self) -> Mapping[Any, Mapping[Any, Mapping[Any, float]]]:
        pass


####################
# MDP Implementation
####################
class MDP(object):
    def __init__(self, game: Game, gamma: float):
        """
        Constructor for an object representing an MDP, built
        from parameters present in a Game object and
        the discount factor (gamma)
        """
        self.gamma = gamma
        self.rewards = game.rewards()
        self.transitions = game.transitions()
        self.actions = game.actions()
        self.states = game.states()
        self.initial_state = game.initial_state()

    def random_trajectory(self, policy):
        """
        Generate and return a random trajectory along
        with the discounted total sum of rewards
        """
        trajectory = []
        s = self.initial_state
        total_reward = 0
        while s in self.transitions:
            a = policy[s]
            next_p = random.random()
            candidates = self.transitions[s][a].items()
            for candidate in candidates:
                next_p = next_p - candidate[1]
                if next_p < 0:
                    r = self.rewards[s][a][candidate[0]]
                    total_reward = total_reward + self.gamma * r
                    trajectory.append((s, a, r))
                    s = candidate[0]
                    break
        trajectory.append((s, None, None))
        return trajectory, total_reward

    def q(self, s, a, values):
        """
        Q value for the chance node <s,a>
        """
        value = 0
        for s_prima in self.states:
            prob = self.transitions.get(s, {}).get(a, {}).get(s_prima, 0)
            reward = self.rewards.get(s, {}).get(a, {}).get(s_prima, 0)
            value = value + prob * (reward + self.gamma * values[s_prima])
        return value

    def policy_evaluation(self, policy, max_iter=1000, epsilon=0.0, debug=False):
        """
        Execute the policy evaluation algorithm
        :param policy: a dictionary mapping actions to states
        :param max_iter: maximum number of iterations before stopping
        :param epsilon: upper bound for the maximum value difference before stopping
        :param debug: whether to print the intermediate value function values
        :return: the value function values after the last iteration
        """
        values = {s: 0 for s in self.states}
        for i in range(max_iter):
            new_values = {}
            for state in self.states:
                action = policy.get(state, -math.inf)
                new_values[state] = self.q(state, action, values)
            max_diff = max(
                [abs(values[state] - new_values[state]) for state in self.states]
            )
            if max_diff <= epsilon:
                if debug:
                    print(f"Converged after {i} iterations")
                break
            values = new_values
            if debug:
                print(f"{new_values}, max_diff = {max_diff}")
        return values

    def value_iteration(self, max_iter=1000, epsilon=0.0, debug=False):
        """
        Execute the value iteration algorithm
        :param max_iter: maximum number of iterations before stopping
        :param epsilon: upper bound for the maximum value difference before stopping
        :param debug: whether to print the intermediate value function values
        :return: tuple with the optimal policy and the value function values after
                 the last iteration
        """
        values = {state: 0 for state in self.states}
        pi_star = {s: None for s in self.states}
        for i in range(max_iter):
            new_values = {}
            pi_star = {}
            for s in self.states:
                q_values = []
                for a in self.transitions.get(s, {}):
                    q_values.append(self.q(s, a, values))
                if len(q_values) == 0:
                    new_values[s] = 0
                    pi_star[s] = None
                else:
                    new_values[s] = max(q_values)
                    pi_star[s] = self.actions[q_values.index(max(q_values))]
            max_diff = max(
                [abs(values[state] - new_values[state]) for state in self.states]
            )
            if debug:
                print(f"{new_values}, max_diff = {max_diff}")
            if max_diff <= epsilon:
                if debug:
                    print(f"Converged after {i} iterations")
                break
            values = new_values
        return pi_star, values


################
# Dice Game (p1)
################
class DiceGame(Game):
    def initial_state(self):
        return "jugando"

    def states(self):
        return ["jugando", "fin"]

    def actions(self):
        return ["jugar", "parar"]

    def transitions(self):
        return {
            "jugando": {"jugar": {"jugando": 2 / 3, "fin": 1 / 3}, "parar": {"fin": 1}}
        }

    def rewards(self):
        return {"jugando": {"jugar": {"jugando": 4, "fin": 4}, "parar": {"fin": 10}}}


######################
# GridWorld (4x3) (p2)
######################
class GridWorld(Game):
    def __init__(self, width, height, base_reward, walls, success, failure):
        super().__init__()
        self.width = width
        self.height = height
        self.base_reward = base_reward
        self.walls = walls
        self.success = success
        self.failure = failure
        self.wrong_headings = {
            "left": ["down", "up"],
            "right": ["up", "down"],
            "up": ["left", "right"],
            "down": ["right", "left"],
        }

    def initial_state(self):
        return (1, 1)

    def states(self):
        states = []
        for i in range(self.width):
            for j in range(self.height):
                states.append((i + 1, j + 1))
        return states

    def actions(self):
        return ["up", "down", "left", "right"]

    def valid_actions(self, s):
        actions = []
        w = s[0]
        h = s[1]
        if s in self.walls or s in self.success or s in self.failure:
            return []
        if w > 1 and (w - 1, h) not in self.walls:
            actions.append("left")
        if w < self.width and (w + 1, h) not in self.walls:
            actions.append("right")
        if h > 1 and (w, h - 1) not in self.walls:
            actions.append("down")
        if h < self.height and (w, h + 1) not in self.walls:
            actions.append("up")
        return actions

    def available_actions(self, s):
        if s in self.walls or s in self.success or s in self.failure:
            return []
        else:
            return ["left", "right", "up", "down"]

    def successor(self, s, a):
        w = s[0]
        h = s[1]
        actions = self.valid_actions(s)
        if a in actions:
            if a == "left":
                return w - 1, h
            elif a == "right":
                return w + 1, h
            elif a == "up":
                return w, h + 1
            elif a == "down":
                return w, h - 1
            else:
                raise NotImplementedError
        else:
            return w, h

    def transitions(self):
        t = {}
        for s in self.states():
            t[s] = {}
            for a in self.available_actions(s):
                t[s][a] = {}
                wrong_headings = self.wrong_headings[a]
                s_1 = self.successor(s, a)
                s_2 = self.successor(s, wrong_headings[0])
                s_3 = self.successor(s, wrong_headings[1])
                t[s][a][s_1] = t[s][a][s_2] = t[s][a][s_3] = 0.0
                t[s][a][s_1] = t[s][a][s_1] + 0.8
                t[s][a][s_2] = t[s][a][s_2] + 0.1
                t[s][a][s_3] = t[s][a][s_3] + 0.1
        return t

    def rewards(self):
        r = {}
        for s in self.states():
            r[s] = {}
            for a in self.available_actions(s):
                r[s][a] = {}
                for s_prima in self.states():
                    if s_prima in self.success:
                        r[s][a][s_prima] = 1
                    elif s_prima in self.failure:
                        r[s][a][s_prima] = -1
                    else:
                        r[s][a][s_prima] = self.base_reward
        return r


#################
# Mars Rover (p3)
#################
class MarsRoverGame(Game):
    def __init__(self, final_states=False):
        super().__init__()
        self.final_states = final_states

    def initial_state(self):
        return 4

    def states(self):
        return [1, 2, 3, 4, 5, 6, 7]

    def actions(self):
        return ["left", "right"]

    def transitions(self):
        transitions = {}
        for s in self.states():
            if not self.final_states or 1 < s < 7:
                transitions[s] = {}
                if s > 1:
                    transitions[s]["left"] = {s - 1: 1}
                else:
                    transitions[s]["left"] = {s: 1}
                if s < 7:
                    transitions[s]["right"] = {s + 1: 1}
                else:
                    transitions[s]["right"] = {s: 1}
        return transitions

    def rewards(self):
        return {
            state: {action: {1: 1, 7: 10} for action in self.actions()}
            for state in self.states()
        }


#######################
# Mars Rover Solar (p4)
#######################
class MarsRoverSolarGame(Game):
    def initial_state(self):
        return random.choice(self.states())

    def states(self):
        return ["H", "M", "L"]

    def actions(self):
        return ["spin", "noop"]

    def transitions(self):
        return {
            "H": {"spin": {"H": 1}, "noop": {"M": 1}},
            "M": {"spin": {"H": 1}, "noop": {"L": 1}},
            "L": {"spin": {"M": 1}, "noop": {"L": 1}},
        }

    def rewards(self):
        return {
            "H": {"spin": {"H": 2}, "noop": {"M": 3}},
            "M": {"spin": {"H": 2}, "noop": {"L": 3}},
            "L": {"spin": {"M": -1}, "noop": {"L": 0}},
        }


####################################
# Drone Delivery (p10, example exam)
####################################
class DroneDelivery(Game):
    def initial_state(self):
        return "W"

    def states(self):
        return [
            "W",
            "ENS",
            "ENR",
            "D",
            "R",
        ]  # Warehouse, En route and sunny, En route and Rainy, Delivered, Returned

    def actions(self):
        return ["fly", "deliver", "wait"]

    def transitions(self):
        return {
            "W": {"fly": {"ENR": 0.5, "ENS": 0.5}, "wait": {"W": 1.0}},
            "ENS": {
                "wait": {"ENR": 0.5, "ENS": 0.5},
                "deliver": {"D": 1.0},
                "fly": {"ENR": 0.5, "ENS": 0.5},
            },
            "ENR": {
                "wait": {"ENR": 0.5, "ENS": 0.5},
                "deliver": {"D": 0.5, "ENR": 0.25, "ENS": 0.25},
                "fly": {"ENR": 0.5, "ENS": 0.5},
            },
            "D": {"fly": {"R": 1.0}, "wait": {"D": 1.0}},
        }

    def rewards(self):
        return {
            "W": {"fly": {"ENR": -2, "ENS": -2}, "wait": {"W": -1}},
            "ENS": {
                "wait": {"ENR": -1, "ENS": -1},
                "deliver": {"D": 6},
                "fly": {"ENR": -2, "ENS": -2},
            },
            "ENR": {
                "wait": {"ENR": -1, "ENS": -1},
                "deliver": {"D": 5, "ENR": -5, "ENS": -5},
                "fly": {"ENR": -2, "ENS": -2},
            },
            "D": {"fly": {"R": 3}, "wait": {"D": -1}},
        }


###################
# Problem solutions
###################
def prob_1_mdp_test():
    game = DiceGame()
    mdp = MDP(game, gamma=1)
    accm_reward = 0
    n_sim = 500
    for _ in range(n_sim):
        trajectory, reward = mdp.random_trajectory({"jugando": "jugar"})
        print(trajectory)
        accm_reward = accm_reward + reward
    print(f"Avg. reward: {accm_reward / n_sim}")


def prob_1_e():
    game = DiceGame()
    mdp = MDP(game, gamma=1)
    optimal_policy, values_optimal = mdp.value_iteration(max_iter=100, debug=True)
    print(optimal_policy)
    print(values_optimal)


def prob_2():
    gen = GridWorld(4, 3, -0.04, walls=[(2, 2)], success=[(4, 3)], failure=[(4, 2)])
    mdp = MDP(gen, gamma=1)
    policy = {
        (1, 1): "up",
        (1, 2): "up",
        (1, 3): "right",
        (2, 1): "left",
        (2, 3): "right",
        (3, 1): "up",
        (3, 2): "up",
        (3, 3): "right",
        (4, 1): "left",
    }
    values_policy = mdp.policy_evaluation(policy, max_iter=1000, debug=False)
    print(values_policy)
    optimal_policy, values_optimal = mdp.value_iteration(max_iter=1000, debug=False)
    print(optimal_policy)
    print(values_optimal)


def prob_3():
    game = MarsRoverGame(final_states=True)
    mdp = MDP(game, gamma=0)
    optimal_policy, values_optimal = mdp.value_iteration(max_iter=5000, debug=True)
    print(optimal_policy)
    print(values_optimal)


def prob_4():
    game = MarsRoverSolarGame()
    mdp = MDP(game, gamma=0.5)
    optimal_policy, values_optimal = mdp.value_iteration(
        max_iter=30, epsilon=0.5, debug=True
    )
    print(optimal_policy)
    print(values_optimal)


def exam_prob_10_drone_delivery():
    game = DroneDelivery()
    mdp = MDP(game, gamma=1)
    optimal_policy, values_optimal = mdp.value_iteration(
        max_iter=1000, epsilon=2, debug=True
    )
    print(optimal_policy)
    print(values_optimal)


if __name__ == "__main__":
    # prob_1_mdp_test()
    # prob_1_e()
    # prob_2()
    # prob_3()
    # prob_4()
    exam_prob_10_drone_delivery()
