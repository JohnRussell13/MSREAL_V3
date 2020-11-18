#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char **argv)
{
	FILE *fp;
	char *str;
	char sval1,sval2,sval3,sval4;
	char tval1,tval2,tval3,tval4;
	size_t num_of_bytes = 6;
	
	char temp;

	while(1)
	{
		//Citanje vrednosti tastera
		fp = fopen ("/dev/switch", "r");
		if(fp==NULL)
		{
			puts("Problem pri otvaranju /dev/switch");
			return -1;
		}

		str = (char *)malloc(num_of_bytes+1); 
		getline(&str, &num_of_bytes, fp); 

		if(fclose(fp))
		{
			puts("Problem pri zatvaranju /dev/switch");
			return -1;
		}


		sval1 = str[2] - 48;
		sval2 = str[3] - 48;
		sval3 = str[4] - 48;
		sval4 = str[5] - 48;
		free(str);


		//Citanje vrednosti tastera
		fp = fopen ("/dev/button", "r");
		if(fp==NULL)
		{
			puts("Problem pri otvaranju /dev/button");
			return -1;
		}


		str = (char *)malloc(num_of_bytes+1); 
		getline(&str, &num_of_bytes, fp); 

		if(fclose(fp))
		{
			puts("Problem pri zatvaranju /dev/button");
			return -1;
		}


		tval1 = str[2] - 48;
		//tval2 = str[3] - 48;
		//tval3 = str[4] - 48;
		//tval4 = str[5] - 48;
		free(str);
		
		if(tval1){
			// Upali diode
			fp = fopen("/dev/led", "w");
			if(fp == NULL)
			{
				printf("Problem pri otvaranju /dev/led\n");
				return -1;
			}
			
			//RACUNANJE IZLAZA
			if(sval4){
				temp += sval1+2*sval2+4*sval3;
			}
			else{
				temp -= (sval1+2*sval2+4*sval3);
			}
			
			fprintf(fp, "%d\n", temp);
			
			if(fclose(fp))
			{
				printf("Problem pri zatvaranju /dev/led\n");
				return -1;
			}
		}

		
		sleep(1);
	}
}
