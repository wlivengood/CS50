/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

int main(void)
{
    //define BYTE as 8 bits and unsigned
    typedef uint8_t BYTE;
    
    //open memory card
    FILE* fp = fopen("card.raw", "r");
    
    //check that memory card can be opened
    if(fp == NULL)
	{	
		fclose(fp);
		fprintf(stderr, "Could not open file\n");
		return 1;
	}
	
	//keep count of jpgs for file names
	int counter = 0;
	
	//keep track of whether outfile is open
	bool open = false;
	
	//create pointer to outfile
	FILE* outptr;
	
	//create buffer space for 512 byte chunks
	BYTE buffer[512];
	
	//read chunks into buffer
	fread(buffer, 512, 1, fp);
    
    //loop while we have a chunk
    while (fread(buffer, 512, 1, fp) > 0)
    {
        //check that chunk contains jpg signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff
        && buffer[3] >= 0xe0)
        {   
            //create array to store filename
            char title[8];
            sprintf(title, "%03d.jpg", counter);
            
            //if outfile not already open, open, write to it, reset indicator.
            //this is to handle the first jpg we encounter.
            if (open == false)
            {
                outptr = fopen(title, "w");
                fwrite(buffer, sizeof(buffer), 1, outptr);
                open = true;
            }
            
            //if outfile already open, write to it, increment counter
            if (open == true)
            {
                fclose(outptr);
                outptr = fopen(title, "w");
                fwrite(buffer, sizeof(buffer), 1, outptr);
                counter++;
            }
        }
        //if no jpg signature found, keep writing to outfile, if open
        else
        {
            if (open == true)
                fwrite(buffer, sizeof(buffer), 1, outptr);
        }
    }
    
    //close the outfile
    if (outptr)
        fclose(outptr);
    
    //close the infile and return
    fclose(fp);
    return 0;
}
