h56625
s 00008/00009/00191
d D 6.4 86/04/28 19:08:46 bloom 5 4
c more comments about syslog, phrasing cleanup
e
s 00016/00016/00184
d D 6.3 86/04/17 19:54:10 bloom 4 3
c clean up diction
e
s 00005/00008/00195
d D 6.2 86/04/17 18:00:45 bloom 3 2
c expand set[ug]id, now setgid daemon, explain use of syslogd by lpd
e
s 00014/00014/00189
d D 6.1 86/04/17 16:46:46 mckusick 2 1
c 4.3BSD beta release document
e
s 00203/00000/00000
d D 5.1 86/04/17 16:46:36 mckusick 1 0
c document distributed with 4.2BSD
e
u
U
t
T
I 1
.\" Copyright (c) 1983 Regents of the University of California.
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
.\"
.\"	%W% (Berkeley) %G%
.\"
.NH 1
Troubleshooting
.PP
D 4
There are a number of messages which may be generated by the
E 4
I 4
There are several messages that may be generated by the
E 4
the line printer system.  This section
categorizes the most common and explains the cause
D 4
for their generation.  Where the message indicates a failure,
E 4
I 4
for their generation.  Where the message implies a failure,
E 4
directions are given to remedy the problem.
.PP
In the examples below, the name
.I printer
D 5
is the name of the printer. 
D 4
This would be one of the names from the
E 4
I 4
This would be a name from the
E 5
I 5
is the name of the printer from the
E 5
E 4
.I printcap
database.
.NH 2
LPR
.SH
lpr: \fIprinter\fP\|: unknown printer
.IP
The
.I printer
was not found in the
.I printcap
database.  Usually this is a typing mistake; however, it may indicate
a missing or incorrect entry in the /etc/printcap file.
.SH
lpr: \fIprinter\fP\|: jobs queued, but cannot start daemon.
.IP
The connection to 
.I lpd
on the local machine failed. 
This usually means the printer server started at
boot time has died or is hung.  Check the local socket
/dev/printer to be sure it still exists (if it does not exist,
there is no 
.I lpd
D 2
process running).  Use
E 2
I 2
process running). 
D 4
Usually it is sufficient to get a super-user to type the following to
E 4
I 4
Usually it is enough to get a super-user to type the following to
E 4
restart
.IR lpd .
E 2
.DS
D 2
% ps ax | fgrep lpd
E 2
I 2
% /usr/lib/lpd
E 2
.DE
D 2
to get a list of process identifiers of running lpd's.
The \fIlpd\fP to kill is the one which is not listed in any
of the ``lock" files (the lock file is contained in the spool directory of
each printer).
Kill the master daemon using the following command.
E 2
I 2
D 4
You can also check on the state of the master printer daemon with the following.
E 4
I 4
You can also check the state of the master printer daemon with the following.
E 4
E 2
.DS
D 2
% kill \fIpid\fP
E 2
I 2
% ps l`cat /usr/spool/lpd.lock`
E 2
.DE
D 2
Then remove /dev/printer and restart the daemon (and printer)
with the following commands.
.DS
% rm /dev/printer
% /usr/lib/lpd
.DE
E 2
.IP
Another possibility is that the
.I lpr
D 3
program is not setuid \fIroot\fP, setgid \fIspooling\fP.
E 3
I 3
program is not set-user-id to \fIroot\fP, set-group-id to group \fIdaemon\fP.
E 3
This can be checked with
.DS
% ls \-lg /usr/ucb/lpr
.DE
.SH
lpr: \fIprinter\fP\|: printer queue is disabled
.IP
This means the queue was turned off with
.DS
% lpc disable \fIprinter\fP
.DE
to prevent 
.I lpr
from putting files in the queue.  This is normally
done by the system manager when a printer is
going to be down for a long time.  The
printer can be turned back on by a super-user with
.IR lpc .
.NH 2
LPQ
.SH
waiting for \fIprinter\fP to become ready (offline ?)
.IP
The printer device could not be opened by the daemon. 
D 4
This can happen for a number of reasons,
the most common being that the printer is turned off-line.
E 4
I 4
This can happen for several reasons,
the most common is that the printer is turned off-line.
E 4
This message can also be generated if the printer is out
of paper, the paper is jammed, etc.
The actual reason is dependent on the meaning
of error codes returned by system device driver. 
D 4
Not all printers supply sufficient information 
E 4
I 4
Not all printers supply enough information 
E 4
to distinguish when a printer is off-line or having
trouble (e.g. a printer connected through a serial line). 
Another possible cause of this message is
some other process, such as an output filter,
has an exclusive open on the device.  Your only recourse
here is to kill off the offending program(s) and
restart the printer with
.IR lpc .
.SH
\fIprinter\fP is ready and printing
.IP
The
.I lpq
program checks to see if a daemon process exists for
.I printer
D 5
and prints the file
.IR status .
E 5
I 5
and prints the file \fIstatus\fP located in the spooling directory.
E 5
If the daemon is hung, a super user can use
.I lpc
to abort the current daemon and start a new one.
.SH
waiting for \fIhost\fP to come up
.IP
D 4
This indicates there is a daemon trying to connect to the remote
E 4
I 4
This implies there is a daemon trying to connect to the remote
E 4
machine named
.I host
D 4
in order to send the files in the local queue. 
E 4
I 4
to send the files in the local queue. 
E 4
If the remote machine is up,
.I lpd
on the remote machine is probably dead or
hung and should be restarted as mentioned for
.IR lpr .
.SH
sending to \fIhost\fP
.IP
The files should be in the process of being transferred to the remote
.IR host .
If not, the local daemon should be aborted and started with
.IR lpc .
.SH
Warning: \fIprinter\fP is down
.IP
The printer has been marked as being unavailable with
.IR lpc .
.SH
Warning: no daemon present
.IP
The \fIlpd\fP process overseeing
D 4
the spooling queue, as indicated in the ``lock'' file
E 4
I 4
the spooling queue, as specified in the ``lock'' file
E 4
in that directory, does not exist.  This normally occurs
only when the daemon has unexpectedly died.
D 5
The error log file for the printer should be checked for a
E 5
I 5
The error log file for the printer and the \fIsyslogd\fP logs
should be checked for a
E 5
diagnostic from the deceased process.
To restart an \fIlpd\fP, use
.DS
% lpc restart \fIprinter\fP
.DE
I 2
.SH
no space on remote; waiting for queue to drain
.IP
D 4
This indicates that there is insufficient disk space on the remote.
E 4
I 4
This implies that there is insufficient disk space on the remote.
E 4
If the file is large enough, there will never be enough space on
the remote (even after the queue on the remote is empty). The solution here
is to move the spooling queue or make more free space on the remote.
E 2
.NH 2
LPRM
.SH
lprm: \fIprinter\fP\|: cannot restart printer daemon
.IP
This case is the same as when
.I lpr
prints that the daemon cannot be started.
.NH 2
LPD
.PP
The
.I lpd
D 3
program can write many different messages to the error log file
(the file specified in the 
.B lf
entry in
.IR printcap ).
E 3
I 3
program can log many different messages using \fIsyslogd\fP\|(8).
E 3
D 4
Most of these messages are about files which can not
be opened and usually indicate the
E 4
I 4
Most of these messages are about files that can not
be opened and usually imply that the
E 4
.I printcap
D 5
file or the protection modes of the files are not
correct.   Files may also be inaccessible if people
E 5
I 5
file or the protection modes of the files are
incorrect.   Files may also be inaccessible if people
E 5
manually manipulate the line printer system (i.e. they
bypass the
.I lpr
program). 
.PP
In addition to messages generated by 
.IR lpd ,
any of the filters that
.I lpd
D 3
spawns may also log messages to this file.
E 3
I 3
D 5
spawns may log messages to the error log file (the file specified in the
\fBlf\fP entry in \fIprintcap\fP\|).
E 5
I 5
spawns may log messages using \fIsyslogd\fP or to the error log file
(the file specified in the \fBlf\fP entry in \fIprintcap\fP\|).
E 5
E 3
.NH 2
LPC
.PP
.SH
D 3
could't start printer
E 3
I 3
couldn't start printer
E 3
.IP
This case is the same as when
.I lpr
reports that the daemon cannot be started.
.SH
cannot examine spool directory
.IP
D 4
Error messages beginning with ``cannot ...'' are usually due to
incorrect ownership and/or protection mode of the lock file, spooling
E 4
I 4
Error messages beginning with ``cannot ...'' are usually because of
incorrect ownership or protection mode of the lock file, spooling
E 4
directory or the
.I lpc
program.
E 1
