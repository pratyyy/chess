#include <stdio.h>
#include <stdlib.h>
#include "object.h"
#include "load_3ds.h"

#include <sys/stat.h>


long filelength(int f)
{
    struct stat buf;

    fstat(f, &buf);

    return(buf.st_size);
}


char Load3DS(obj_type_ptr p_object, char *p_filename)
{
	int i; //Index variable
	
	FILE *l_file; //File pointer
	
	unsigned short l_chunk_id; //Chunk identifier
	unsigned int l_chunk_length; //Chunk length

	unsigned char l_char; //Char variable
	unsigned short l_qty; //Number of elements in each chunk

	unsigned short l_face_flags; //Flag that stores some face information

	if (p_filename=='\0') return(0);

	if ((l_file=fopen (p_filename, "rb"))== NULL) 
	{

		return (0);
	}

	while (ftell (l_file) < filelength (fileno (l_file))) //Loop to scan the whole file 
	{
		//getche(); //Insert this command for debug (to wait for keypress for each chuck reading)

		fread (&l_chunk_id, 2, 1, l_file); //Read the chunk header
		//printf("ChunkID: %x\n",l_chunk_id); 
		fread (&l_chunk_length, 4, 1, l_file); //Read the length of the chunk
		//printf("ChunkLength: %x\n",l_chunk_length);

		switch (l_chunk_id)
        {

			case 0x4d4d: 
			break;    

		
			case 0x3d3d:
			break;
			

			case 0x4000: 
				i=0;
				do
				{
					fread (&l_char, 1, 1, l_file);
                    p_object->name[i]=l_char;
					i++;
                }while(l_char != '\0' && i<20);
			break;


			case 0x4100:
			break;
			

			case 0x4110: 
				fread (&l_qty, sizeof (unsigned short), 1, l_file);
                p_object->vertices_qty = l_qty;
                //printf("Number of vertices: %d\n",l_qty);
				if (l_qty>MAX_VERTICES) 
				{
			      
					return (0);
				}
                for (i=0; i<l_qty; i++)
                {
					fread (&p_object->vertex[i].x, sizeof(float), 1, l_file);
 					//printf("Vertices list x: %f\n",p_object->vertex[i].x);
                    fread (&p_object->vertex[i].y, sizeof(float), 1, l_file);
 					//printf("Vertices list y: %f\n",p_object->vertex[i].y);
					fread (&p_object->vertex[i].z, sizeof(float), 1, l_file);
 					//printf("Vertices list z: %f\n",p_object->vertex[i].z);
				}
				break;


			case 0x4120:
				fread (&l_qty, sizeof (unsigned short), 1, l_file);
                p_object->polygons_qty = l_qty;
                //printf("Number of polygons: %d\n",l_qty); 
				if (l_qty>MAX_POLYGONS) 
				{

					return (0);
				}				
                for (i=0; i<l_qty; i++)
                {
					fread (&p_object->polygon[i].a, sizeof (unsigned short), 1, l_file);
					//printf("Polygon point a: %d\n",p_object->polygon[i].a);
					fread (&p_object->polygon[i].b, sizeof (unsigned short), 1, l_file);
					//printf("Polygon point b: %d\n",p_object->polygon[i].b);
					fread (&p_object->polygon[i].c, sizeof (unsigned short), 1, l_file);
					//printf("Polygon point c: %d\n",p_object->polygon[i].c);
					fread (&l_face_flags, sizeof (unsigned short), 1, l_file);
					//printf("Face flags: %x\n",l_face_flags);
				}
                break;


			case 0x4140:
				fread (&l_qty, sizeof (unsigned short), 1, l_file);
				for (i=0; i<l_qty; i++)
				{
					fread (&p_object->mapcoord[i].u, sizeof (float), 1, l_file);
					//printf("Mapping list u: %f\n",p_object->mapcoord[i].u);
                    fread (&p_object->mapcoord[i].v, sizeof (float), 1, l_file);
					//printf("Mapping list v: %f\n",p_object->mapcoord[i].v);
				}
                break;


			default:
				 fseek(l_file, l_chunk_length-6, SEEK_CUR);
        } 
	}
	fclose (l_file); // Closes the file stream
	return (1); // Returns ok
}
