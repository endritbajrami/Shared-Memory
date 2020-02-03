#include &lt;sys/types.h&gt;
#include &lt;sys/ipc.h&gt;
#include &lt;sys/shm.h&gt;
#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;ctype.h&gt;
#define SHMSZ 100

main()
{
int shmid;
key_t key;
char *shm, *s, *p;
key = 888;
//Krijimi i shared memory segmentit dhe ruajtja e id ne shmid (-1 ne rast deshtimi, vlere
integer pozitive nese ka sukses)
shmid = shmget(key, SHMSZ, IPC_CREAT | 0666);

//Kontrollimi nese eshte krijuar shared memory segmenti
if (shmid &lt; 0)
{
perror(&quot;shmget error&quot;);
exit(1);
}
//Mapimi i shared memory segmentit ne hapesiren e procesit
if ((shm = shmat(shmid, NULL, 0)) == (char *) -1)
{
perror(&quot;shmat error&quot;);
exit(1);
}
s = shm;
char array[100];
int i=0;
int z, y;
char Fprog[] = &quot;Enter the cipher key: &quot;;
char Vprog[] = &quot;Enter the sentence: &quot;;
//Vendosja e Fprog ne shared memory
for(i=0; i&lt; sizeof(Fprog); i++)
{
*s++ = Fprog[i];
}
//Pozicionojme pointerin &#39;s&#39; ne fillim te shared memory&#39;s dhe presim qe vlera ne fillim
te mos jete shkronje (ne rastin tone &#39;E&#39;)
s = shm;
while(isalpha(*s))



{
sleep(1);
}
z= *s - &#39;0&#39;; //char to int
//Pas ndryshimit te vleres se pare ne shared memory shkruajme vleren e Vprog
for(i=0; i&lt;sizeof(Vprog); i++)
{
*s++ = Vprog[i];
}
//Pozicionojme pointerin &#39;s&#39; ne fillim te shared memory&#39;s dhe presim qe vlera ne fillim
te mos jete &#39;E&#39;
s = shm;
while(*s==&#39;E&#39;)
{
sleep(1);
}
//Ruajme karakteret e shared memory prej fillimit derisa te mos jete NULL
s = shm;
int k=0;
for(s=shm; *s!=NULL; s++)
{
array[k]=*s;
k++;
}
s = shm;
char size;
int size2;
//I shtojme ne Fuprog vleren per enkriptim dhe gjatesine e saj
char Fuprog[100] = &quot;Your encrypted sentence: &quot;;
for(int k = 0; array[k] != NULL; k++)
{
if(isdigit(array[k]))
{
size = array[k];
goto vazhdo;
}
else if(isalpha(array[k]))
{
Fuprog[k+25] = array[k];
}
}
vazhdo:



size2 = size - &#39;0&#39;;
s=shm;
//Enkriptojme vleren dhe e ruajme ne Fuprog
for(int l=25; Fuprog[l] != NULL ; l++)
{
y = ((int)Fuprog[l] + z - 97)%26 +97;
Fuprog[l]=(char)y;
}
//Shkruajme vleren e Fuprog ne Shared Memory
for(int i=0; Fuprog[i] != NULL ; i++)
{
*s++ = Fuprog[i];
}
//Fshijme segmentin e krijuar
shmctl(shmid,IPC_RMID,0);
exit(0);
}
