!
! BOOTSTRAP BY BOOT() SYSCALL
! GO MULTI-USER AFTER CHECKING; BOOT FROM DEFAULT DEVICE
!
LOAD BOOT
D/G B 0		! BOOT PARAMETERS: MULTI USER AFTER CHECK
D/G A 10	! DEV TO BOOT FROM (16=RA ON KDB50, CHANGE TO 9 IF UDA50)
START 2
