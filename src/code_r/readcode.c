#include "readcode.h"

int i=0; // for line numbering
short isComment(char *line_buf)
{
		if((strstr(line_buf,"//@"))!= 0)
		{
			return 1;
		}
		else
		{
			return 0;
		}
}
char *deleteComment(char *line_buf)
{
	int j=0;
	for(j=0; j<strlen(line_buf); j++)
	{
		line_buf[j] = line_buf[j+4];
	}
	line_buf[strlen(line_buf)] = '\0';
	return line_buf;
}
void addToText(char *feed, LINE **HEAD)
{
	LINE *NEW = (LINE *)malloc(sizeof(LINE));
	NEW->text = (char *)malloc(sizeof(feed)*SZ_BUF);
	NEW->NEXT = 0; NEW->type = isComment(feed);
	if(NEW->type == SRC_LINE) // If the type of line is source
	{
		i++;	
		strcpy(NEW->text, feed);
	}
	else // If the line is comment line, then delete "//@"
	{
		strcpy(NEW->text, deleteComment(feed));
	}
	NEW->line_index = i;
	if((*HEAD) == 0)
	{
		(*HEAD) = NEW;
	}
	else
	{
		LINE *CUR = (*HEAD);
		while(CUR->NEXT != 0)
		{
			CUR = CUR->NEXT;
		}
		CUR->NEXT = NEW;
	}
}
void displayText(LINE *HEAD) // For testing.
{
	LINE *CUR = HEAD;
	while(CUR != 0)
	{
		if(CUR->type == COM_LINE)
		{
				printf("\x1B[31m"); // Set the line color Red
		}
		else
		{
				printf("\x1B[0m");
		}
		printf("%d:%s\n",CUR->line_index,CUR->text);
		CUR = CUR->NEXT;
	}		
}
LINE *ReadFile(char *filename)
{
	LINE *para = 0;
	FILE *infile;
	char line_buf[SZ_BUF];

	infile = fopen(filename,"r");
	if(!infile)
	{
		perror("File");
		return NULL;
	}	

	while(fgets(line_buf,SZ_BUF, infile))
	{
		line_buf[sizeof(line_buf)-1] = '\0';
		addToText(line_buf,&para);
	}
	
	return para;
}
