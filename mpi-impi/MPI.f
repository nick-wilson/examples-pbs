C     Sample program: sample2.f
C     Copyright (C) 2003, Fujitsu Limited, All Rights Reserved. 
C     $Id: sample2.f,v 1.2 2003/10/09 22:27:32 matsu Exp $ 

      PROGRAM sample2_f
      INCLUDE 'mpif.h'

      INTEGER rank, size, root, ierror
      INTEGER data, result
      CHARACTER ( LEN = MPI_MAX_PROCESSOR_NAME ) :: procname
      INTEGER :: namelen , error

      result = -100

      CALL MPI_INIT( ierror )
      CALL MPI_COMM_RANK( MPI_COMM_WORLD, rank, ierror )
      CALL MPI_COMM_SIZE( MPI_COMM_WORLD, size, ierror )

      CALL MPI_Get_processor_name ( procname , namelen , error )
      WRITE(*,*) "Rank=",rank,"Name=",procname
      IF ( rank .EQ. 0 ) THEN  
         WRITE(*,*) 'MPI communication start. size=',size
      ENDIF

      data = rank

      root = 0
      CALL MPI_REDUCE( data, result, 1, MPI_INTEGER, MPI_SUM, root,
     &                 MPI_COMM_WORLD, ierror )

      IF (rank .EQ. 0) THEN  
         WRITE(*,*) 'MPI communication end'
         WRITE(*,*) 'result is 0+1+...size-1.check result(',result,')'
      ENDIF

      CALL MPI_FINALIZE( ierror )
      STOP
      END
