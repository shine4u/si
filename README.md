si
==

simple interface cpp

si is short for simple interface.
it consists of group of defines and wrapper class for commmon use.

BasicDefs.h:
1) simple macros
2) simple inline functions

Logger.h: BasicDefs.h
1) function that handle logger settings.
2) macros about logger and block control with logging.

StrHelper.h: Logger.h
1) static funtions that handle std::string

Configer.h: Logger.h
1) configer of xml.
