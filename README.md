ScoreSys
========

Martial Arts Tournament Scoreboard

-----------
Containing:

a UDP enabled ScoreBoard to display the combatants
and their scores, as well as their penalties.

a MasterServer to handle storing of combatants, 
controlling JudgesTables and assigning ScoreBoards
to them.

a JudgesTable to update its assigned ScoreBoards,
retreive the combatants from the MasterServer and
return the bout's outcome to the MasterServer

------------
Compilation:

this should build all the modules and programs needed
$ qmake && make

