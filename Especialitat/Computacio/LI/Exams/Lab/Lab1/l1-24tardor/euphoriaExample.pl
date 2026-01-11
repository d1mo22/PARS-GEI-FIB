% numberOfSongsForConcert(N):
% N songs are sung in the concert.
numberOfSongsForConcert(20).

% minNumberOfSongsOfType(M, T):
% in the concert there are at least M songs of type T.
minNumberOfSongsOfType(3,      dance).
minNumberOfSongsOfType(3, flashlight).

% inWindowOfThisSizeAtMostOneOfType(W, T):
% in a window of W consecutive song slots, at most one is of type T.
inWindowOfThisSizeAtMostOneOfType(4,      dance).
inWindowOfThisSizeAtMostOneOfType(4, flashlight).

%%    Id                             Title   Score          Type     Participant
data(  1,                    'Tu es foutu',      8,      regular,        'Julien').
data(  2,            'Great balls of fire',      7,        dance,        'Julien').
data(  3,                        'Bon dia',      6,        dance,        'Julien').
data(  4,            'Baby don\'t hurt me',      6,      regular,        'Julien').
data(  5,                         'Corren',      5,      regular,         'Lluís').
data(  6,                       'Bailoteo',      7,        dance,         'Lluís').
data(  7,                   'Lose control',      6,      regular,         'Lluís').
data(  8,                       'Wa yeah!',      8,        dance,         'Lluís').
data(  9,                    'Blank space',      7,      regular,         'Maria').
data( 10,                       'Symphony',      8,      regular,         'Maria').
data( 11,                          'Creep',      9,   flashlight,         'Maria').
data( 12,            'The show must go on',      8,   flashlight,         'Maria').
data( 13,                           'Torn',      7,      regular,         'Misty').
data( 14,                       'Diamonds',      8,      regular,         'Misty').
data( 15,                  'Eternal flame',      9,   flashlight,         'Misty').
data( 16,                 'Girl gone wild',      6,      regular,         'Misty').
data( 17,                        'Valerie',      6,      regular,       'Valeria').
data( 18,                           'Lobo',      7,      regular,       'Valeria').
data( 19,                  'Els teus ulls',      6,   flashlight,       'Valeria').
data( 20,                            'SOS',      6,      regular,       'Fredrik').
data( 21,                   'Grande amore',      7,      regular,       'Fredrik').
data( 22,               'Nothing compares',      8,   flashlight,     'Xavi Noms').
data( 23,                    'A poc a poc',      7,      regular,     'Xavi Noms').
data( 24,            'Million dollar baby',      6,      regular, 'Aina Da Silva').
data( 25,       'Dancing in the Moonlight',      5,      regular, 'Aina Da Silva').
data( 26,                     'Chandelier',      6,      regular,         'Lluna').
data( 27,                     'Girlfriend',      5,      regular,         'Lluna').
data( 28,                     'Tant de bo',      6,      regular,          'Bita').
data( 29,                      'Rich girl',      5,      regular,          'Bita').
data( 30,                      'La platja',      6,        dance,   'Pau Culleré').
data( 31, 'La petita rambla del poble-sec',      5,      regular,        'Rangel').
data( 32,                      'I love it',      4,      regular,           'Yuk').
data( 33,              'Paraules paraules',      3,      regular,        'Dounia').
data( 34,                   'La meva sort',      3,      regular,        'Tamara').
data( 35,                'Blinding lights',      2,      regular,          'Hugo').