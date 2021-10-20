python binding for https://github.com/Ja-sonYun/sequence-diagram-cli

DESCRIPTION
-----------

    - seqdia wrapped by python c api

HOW TO BUILD
------------

    - python setup.py build && python setup.py install

EXAMPLE USAGE
-------------

>>> import seqdia
>>> def seqdia_printer(diagram):
...     for line in diagram: print(line)
...
>>> array = [
...     'participant "Initiator" as I',
...     'participant "Receiver" as R',
...     "I->R: FIN",
...     "I<--R: ACK",
...     "R->I: FIN",
...     "I-->R: ACK",
...     "I->I: Closed",
...     "R->R: Closed",
... ]
>>> diagram = seqdia.generate_from_array(array)
>>> seqdia_printer(diagram)
╭───────────╮╭──────────╮
│ Initiator ││ Receiver │
╰─────┬─────╯╰─────┬────╯
      │            │
      │            │
      │    FIN     │
      ├╌╌╌╌╌╌╌╌╌╌╌▶│
      │            │
      │    ACK     │
      │≺╴╴╴╴╴╴╴╴╴╴╴┤
      │            │
      │    FIN     │
      │◀╌╌╌╌╌╌╌╌╌╌╌┤
      │            │
      │    ACK     │
      ├╶╶╶╶╶╶╶╶╶╶╶≻│
      │            │
      │ Closed     │
      ├╌╌╌╌╌╌╌╮    │
      │       │    │
      │◀╌╌╌╌╌╌╯    │
      │            │
      │            │ Closed
      │            ├╌╌╌╌╌╌╌╮
      │            │       │
      │            │◀╌╌╌╌╌╌╯
      │            │
>>> diagram_al = seqdia.generate_from_array(array, "al")
>>> seqdia_printer(diagram_al)
,-----------.,----------.
| Initiator || Receiver |
`-----------'`----------'
      |            |
      |            |
      |    FIN     |
      +----------->|
      |            |
      |    ACK     |
      |<...........+
      |            |
      |    FIN     |
      |<-----------+
      |            |
      |    ACK     |
      +...........>|
      |            |
      | Closed     |
      +-------.    |
      |       |    |
      |<------'    |
      |            |
      |            | Closed
      |            +-------.
      |            |       |
      |            |<------'
      |            |
>>> something_wrong = ["sad?-=>jd"]
>>> diagram_wrong = seqdia.generate_from_array(something_wrong)
>>> print(diagram_wrong)
0  # print line that failed to parse
>>> something_wrong = ["A->s:asd", "sadaskldj_+!?#R+"]
>>> diagram_wrong = seqdia.generate_from_array(something_wrong)
>>> diagram_wrong
1  # print line that failed to parse
>>>

