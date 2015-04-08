Redesigning the UDP communication with the score_board
======================================================

to this setup:

* startup selecting a random port and broadcast "needUi <port>"
* wait for UDPs to arrive "SetUI '<title>' [<req_style>]"
* wait for timer commands "timer {start|stop} [MM:SS:%%] | reset MM:SS:00"
* wait for player updates "player {r|l} name'<name>' pt:XX [...]"
