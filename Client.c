#include &lt;sys/types.h&gt;
#include &lt;sys/ipc.h&gt;
#include &lt;sys/shm.h&gt;
#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;ctype.h&gt;
#define SHMSZ 100
main()
{
int shmid, temp, i;
key_t key;
char *shm, *s, tempc[100];
key = 888;
//Permes celesit te njejte gjejme shmid e segmentit te krijuar nga serveri
shmid = shmget(key, SHMSZ, 0666);



if (shmid &lt; 0)
{
perror(&quot;shmget error&quot;);
exit(1);
}
if ((shm = shmat(shmid, NULL, 0)) == (char *) -1)
{
perror(&quot;shmat error&quot;);
exit(1);
}
//Shfaqim vleren e shmid (e cila perdoret nga shmctl.c)
printf(&quot;Shmid=%d\n&quot;,shmid);
//Shfaqim ne console vleren e shkruajtur nga serveri (Enter the cipher key: ) dhe
presim nga klienti te jap vleren e key
for (s = shm; *s != NULL; s++)
{
putchar(*s);
}
s = shm;
scanf(&quot;%d&quot;,&amp;temp);
temp = temp % 26;
*s = temp+&#39;0&#39;; // int to char
//Pointojme ne fillim te shared memory dhe presim derisa vlera te mos jete numer
(vlera e key ne rastin tone)
s=shm;
while(isdigit(*s))
{
sleep(1);
}
//Shfaqim ne console vleren e re te shkruajtur nga serveri dhe presim nga klienti te
shkruaje vleren per enkriptim
for (s = shm; *s != NULL; s++)
putchar(*s);
scanf(&quot;%s&quot;, &amp;tempc);
s = shm;
int size = 0;
char size2;


//Shkruajme vleren per enkriptim dhe gjatesine e vleres duke filluar nga adresa e pare
e shared memory
for(int t=0; tempc[t]!= NULL; t++)
{
*s++ = tempc[t];
size++;
}
size2 = size + &#39;0&#39;;
*s = size2;
//Presim derisa serveri te enkriptoje vleren e dhene
sleep(1);
//Shfaqim vleren ne ekran (Your encrypted sentece: .... )
for (s = shm; *s != NULL; s++)
putchar(*s);
putchar(&#39;\n&#39;);
exit(0);
}