# Meeting-Data-Visualizer-Specification

Due to the social distancing and travel restrictions all around the world, people have moved most
of the work to virtual environments. Due to this, the usage of meeting tools has exponentially
increased so as the data gathered through such tools. The objective of this project is to analyze such
data files and visually represent the data as per the requirement of user.


## Meetings/participants/duration Representation
The program can analyse three different parameters, No. of Meetings, No. of Participants and
Duration. If the output should list meetings, the −m should be given. If the output should list
participant counts, the −p should be given. If the output should list time duration, the −t should be
given.

you may use the following static pattern of the command line arguments
to run the program.

`./prog − m − −scaled − l 10 f ile1 f ile2 f ile3 ...`

where, -m can be changed to either -t or -p and 10 can be any positive integer.
