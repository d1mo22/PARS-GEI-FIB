import gymnasium
import numpy as np
from gymnasium.spaces import Discrete
from pettingzoo import AECEnv
from pettingzoo.utils import agent_selector, wrappers
from pettingzoo.utils.conversions import parallel_wrapper_fn


class raw_env(AECEnv):
    metadata = {
        "render_modes": ["human"],
        "name": "simple_pd_v0",
        "is_parallelizable": True,
    }

    def __init__(self, game="pd", num_actions=2, max_cycles=15, render_mode=None):
        self.max_cycles = max_cycles
        self.render_mode = "human"
        self.name = "simple_pd_v0"
        self.game = Prisoners_Dilemma()
        self._moves = self.game.moves
        self._none = self.game.NONE
        self.agents = ["player_" + str(r) for r in range(2)]
        self.possible_agents = self.agents[:]
        self.agent_name_mapping = dict(
            zip(self.agents, list(range(self.num_agents)))
        )
        self.action_spaces = {
            agent: Discrete(num_actions) for agent in self.agents
        }
        self.observation_spaces = {
            agent: Discrete(1 + num_actions) for agent in self.agents
        }
        self.render_mode = render_mode
        self.reinit()

    def observation_space(self, agent):
        return self.observation_spaces[agent]

    def action_space(self, agent):
        return self.action_spaces[agent]

    def reinit(self):
        self.agents = self.possible_agents[:]
        self._agent_selector = agent_selector(self.agents)
        self.agent_selection = self._agent_selector.next()
        self.rewards = {agent: 0 for agent in self.agents}
        self._cumulative_rewards = {agent: 0 for agent in self.agents}
        self.terminations = {agent: False for agent in self.agents}
        self.truncations = {agent: False for agent in self.agents}
        self.infos = {agent: {} for agent in self.agents}

        self.state = {agent: self._none for agent in self.agents}
        self.observations = {
            agent: [self._none] * len(self.possible_agents)
            for agent in self.agents
        }

        self.history = [0] * (2 * 5)

        self.num_moves = 0

    def render(self):
        if self.render_mode is None:
            gymnasium.logger.warn(
                "You are calling render method without specifying any render mode."
            )
            return

        if len(self.agents) == 2:
            string = "Current state: Agent1: {} , Agent2: {}".format(
                self._moves[self.state[self.agents[0]]],
                self._moves[self.state[self.agents[1]]],
            )
        else:
            string = "Game over"
        print(string)

    def observe(self, agent):
        # observation of one agent is the previous state of the other
        return np.array(self.observations[agent])

    def close(self):
        pass

    def reset(self, seed=None, return_info=False, options=None):
        self.reinit()

    def step(self, action):
        if (
                self.terminations[self.agent_selection]
                or self.truncations[self.agent_selection]
        ):
            self._was_dead_step(action)
            return

        agent = self.agent_selection

        self.state[self.agent_selection] = action

        if self._agent_selector.is_last():
            (
                self.rewards[self.agents[0]],
                self.rewards[self.agents[1]],
            ) = self.game.payoff[
                (self.state[self.agents[0]], self.state[self.agents[1]])
            ]

            self.num_moves += 1
            self.truncations = {
                agent: self.num_moves >= self.max_cycles
                for agent in self.agents
            }

            # observe the current state
            for i in self.agents:
                self.observations[i] = list(
                    self.state.values()
                )
        else:
            self.state[
                self.agents[1 - self.agent_name_mapping[agent]]
            ] = self._none
            self._clear_rewards()

        self._cumulative_rewards[self.agent_selection] = 0
        self.agent_selection = self._agent_selector.next()
        self._accumulate_rewards()

        if self.render_mode == "human":
            self.render()


class Game:
    def __init__(self, num_iters=1000):
        self.moves = []
        self.num_iters = num_iters

    def get_payoff(self):
        pass

    def get_num_iters(self):
        return self.num_iters


class Prisoners_Dilemma(Game):
    def __init__(self):
        super().__init__()
        self.COOPERATE = 0
        self.DEFECT = 1
        self.NONE = 2
        self.moves = ["COOPERATE", "DEFECT", "None"]

        self.coop = -1  # I cooperate, they cooperate
        self.defect = -5  # I defect, they defect
        self.temptation = 0  # I defect, they cooperate
        self.sucker = -20  # I cooperate, they defect

        self.payoff = {
            (self.COOPERATE, self.COOPERATE): (self.coop, self.coop),
            (self.COOPERATE, self.DEFECT): (self.sucker, self.temptation),
            (self.DEFECT, self.COOPERATE): (self.temptation, self.sucker),
            (self.DEFECT, self.DEFECT): (self.defect, self.defect),
        }

    def get_payoff(self):
        return self.payoff


def env(**kwargs):
    env = raw_env(**kwargs)
    env = wrappers.AssertOutOfBoundsWrapper(env)
    env = wrappers.OrderEnforcingWrapper(env)
    return env


parallel_env = parallel_wrapper_fn(env)
