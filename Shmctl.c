#include &lt;stdio.h&gt;
#include &lt;sys/types.h&gt;
#include &lt;sys/ipc.h&gt;
#include &lt;sys/shm.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;errno.h&gt;

#define Size 50
main()
{
extern int errno;


int uid, gid, mode;
int rtrn, shmid, command, choice;
struct shmid_ds shmid_ds, *buf;
buf = &amp; shmid_ds;

//Marrim vleren e shmid
printf(&quot;Enter the shmid = &quot;);
scanf(&quot;%d&quot;, &amp;shmid);
printf(&quot;\nEnter the number for\n&quot;);
printf(&quot;the desired command:\n&quot;);

//Marrim njeren nga komandat e funksionit shmctl te listuara
printf(&quot;IPC_STAT = 1\n&quot;);
printf(&quot;IPC_SET = 2\n&quot;);
printf(&quot;IPC_RMID = 3\n&quot;);
printf(&quot;SHM_LOCK = 4\n&quot;);
printf(&quot;SHM_UNLOCK = 5\n&quot;);
printf(&quot;Entry = &quot;);
scanf(&quot;%d&quot;, &amp;command);

printf (&quot;\nshmid =%d, command = %d\n&quot;, shmid, command);

//E ekzekutojme shmctl me komanden e zgjedhur me lart
switch (command)
{
//Ekzekutimi i komandes IPC_STAT


case 1:
rtrn = shmctl(shmid, IPC_STAT,
buf);
printf (&quot;\nThe USER ID = %d\n&quot;, buf-&gt;shm_perm.uid);
printf (&quot;The GROUP ID = %d\n&quot;, buf-&gt;shm_perm.gid);
printf (&quot;The creator&#39;s ID = %d\n&quot;, buf-&gt;shm_perm.cuid);
printf (&quot;The creator&#39;s group ID = %d\n&quot;, buf-&gt;shm_perm.cgid);
printf (&quot;The operation permissions = 0%o\n&quot;, buf-&gt;shm_perm.mode);
printf (&quot;The segment size = %d\n&quot;, buf-&gt;shm_segsz);
printf (&quot;The pid of last shmop = %d\n&quot;, buf-&gt;shm_lpid);
printf (&quot;The pid of creator = %d\n&quot;, buf-&gt;shm_cpid);
printf (&quot;The current # attached = %d\n&quot;, buf-&gt;shm_nattch);
printf(&quot;The last shmat time = %ld\n&quot;, buf-&gt;shm_atime);
printf(&quot;The last shmdt time = %ld\n&quot;, buf-&gt;shm_dtime);
printf(&quot;The last change time = %ld\n&quot;, buf-&gt;shm_ctime);
break;

//Ekzekutimi i komandes IPC_SET
case 2:
rtrn = shmctl(shmid, IPC_STAT, buf);
printf(&quot;\nEnter the number for the\n&quot;);
printf(&quot;member to be changed:\n&quot;);
printf(&quot;shm_perm.uid = 1\n&quot;);
printf(&quot;shm_perm.gid = 2\n&quot;);
printf(&quot;shm_perm.mode = 3\n&quot;);
printf(&quot;Entry = &quot;);
scanf(&quot;%d&quot;, &amp;choice);



//Zgjedhim vleren per ndryshim permes IPC_SET
switch(choice){
case 1:
printf(&quot;\nEnter USER ID = &quot;);
scanf (&quot;%d&quot;, &amp;uid);
buf-&gt;shm_perm.uid = uid;
printf(&quot;\nUSER ID = %d\n&quot;, buf-&gt;shm_perm.uid);
break;
case 2:
printf(&quot;\nEnter GROUP ID = &quot;);
scanf(&quot;%d&quot;, &amp;gid);
buf-&gt;shm_perm.gid = gid;
printf(&quot;\nGROUP ID = %d\n&quot;, buf-&gt;shm_perm.gid);
break;
case 3:
printf(&quot;\nEnter MODE in octal = &quot;);
scanf(&quot;%o&quot;, &amp;mode);
buf-&gt;shm_perm.mode = mode;
printf(&quot;\nMODE = 0%o\n&quot;, buf-&gt;shm_perm.mode);
break;
}
rtrn = shmctl(shmid, IPC_SET, buf);
break;

//Ekzekutimi i komandes IPC_RMID
case 3:



rtrn = shmctl(shmid, IPC_RMID, (struct shmid_ds *) NULL);
break;

//Ekzekutimi i komandes SHM_LOCK
case 4:
rtrn = shmctl(shmid, SHM_LOCK, (struct shmid_ds *) NULL);
break;

//Ekzekutimi i komandes SHM_UNLOCK
case 5:
rtrn = shmctl(shmid, SHM_UNLOCK, (struct shmid_ds *) NULL);
break;
}
//Tregojme se a ishte ekzekutimi i shmctl funksionit
if(rtrn == -1)
{
printf (&quot;\nThe shmctl call failed, error number = %d\n&quot;, errno);
}
else
printf (&quot;\nShmctl was successful for shmid = %d\n&quot;, shmid);
exit (0);
}