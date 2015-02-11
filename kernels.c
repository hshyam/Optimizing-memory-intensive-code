/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/* 
 * Please fill in the following team struct 
 */
team_t team = {
    "X500",              /* Team name */

    "First Lastname",     /* First member full name */
    "X500@nowhere.edu",  /* First member email address */

    "",                   /* Second member full name (LEAVE BLANK) */
    ""                    /* Second member email addr (LEAVE BLANK) */
};

/***************
 * ROTATE KERNEL
 ***************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/

/* 
 * naive_rotate - The naive baseline version of rotate 
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
}

/* 
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr[] = "rotate: Current working version";
void rotate(int dim, pixel *src, pixel *dst) 
{
     int num;
     int size = dim * dim - dim;
     int i,j;

    for(i = 0; i < dim; i+=32) 
        for(j = 0; j < dim; j++) {
        
        num = size - j * dim;
        int m = i * dim +j;
        
            dst[num + i] = src[m];
            dst[num + (i + 1)] = src[m += dim];
            dst[num + (i + 2)] = src[m += dim];
            dst[num + (i + 3)] = src[m += dim];
            dst[num + (i + 4)] = src[m += dim];
            dst[num + (i + 5)] = src[m += dim];
            dst[num + (i + 6)] = src[m += dim];
            dst[num + (i + 7)] = src[m += dim];
            dst[num + (i + 8)] = src[m += dim];
            dst[num + (i + 9)] = src[m += dim];
            dst[num + (i + 10)] = src[m += dim];
            dst[num + (i + 11)] = src[m += dim];
            dst[num + (i + 12)] = src[m += dim];
            dst[num + (i + 13)] = src[m += dim];
            dst[num + (i + 14)] = src[m += dim];
            dst[num + (i + 15)] = src[m += dim]; 
            dst[num + (i + 16)] = src[m += dim];
            dst[num + (i + 17)] = src[m += dim];
            dst[num + (i + 18)] = src[m += dim];
            dst[num + (i + 19)] = src[m += dim];
            dst[num + (i + 20)] = src[m += dim];
            dst[num + (i + 21)] = src[m += dim];
            dst[num + (i + 22)] = src[m += dim];
            dst[num + (i + 23)] = src[m += dim];
            dst[num + (i + 24)] = src[m += dim];
            dst[num + (i + 25)] = src[m += dim];
            dst[num + (i + 26)] = src[m += dim];
            dst[num + (i + 27)] = src[m += dim];
            dst[num + (i + 28)] = src[m += dim];
            dst[num + (i + 29)] = src[m += dim];
            dst[num + (i + 30)] = src[m += dim];
            dst[num + (i + 31)] = src[m += dim];
            
        }
}  
            
            
            
            
            
            
            
            
/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_rotate_functions() 
{
    add_rotate_function(&naive_rotate, naive_rotate_descr);   
    add_rotate_function(&rotate, rotate_descr);   
    /* ... Register additional test functions here */
}


/***************
 * SMOOTH KERNEL
 **************/

/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct {
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;

/* Compute min and max of two integers, respectively */
static int min(int a, int b) { return (a < b ? a : b); }
static int max(int a, int b) { return (a > b ? a : b); }

/* 
 * initialize_pixel_sum - Initializes all fields of sum to 0 
 */
static void initialize_pixel_sum(pixel_sum *sum) 
{
    sum->red = sum->green = sum->blue = 0;
    sum->num = 0;
    return;
}

/* 
 * accumulate_sum - Accumulates field values of p in corresponding 
 * fields of sum 
 */
static void accumulate_sum(pixel_sum *sum, pixel p) 
{
    sum->red += (int) p.red;
    sum->green += (int) p.green;
    sum->blue += (int) p.blue;
    sum->num++;
    return;
}

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) 
{
    current_pixel->red = (unsigned short) (sum.red/sum.num);
    current_pixel->green = (unsigned short) (sum.green/sum.num);
    current_pixel->blue = (unsigned short) (sum.blue/sum.num);
    return;
}

/* 
 * avg - Returns averaged pixel value at (i,j) 
 */
static pixel avg(int dim, int i, int j, pixel *src) 
{
    int ii, jj;
    pixel_sum sum;
    pixel current_pixel;

    initialize_pixel_sum(&sum);
    for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++) 
	for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++) 
	    accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);

    assign_sum_to_pixel(&current_pixel, sum);
    return current_pixel;
}

/******************************************************
 * Your different versions of the smooth kernel go here
 ******************************************************/

/*
 * naive_smooth - The naive baseline version of smooth 
 */
char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
}

/*
 * smooth - Your current working version of smooth. 
 * IMPORTANT: This is the version you will be graded on
 */
char smooth_descr[] = "smooth: Current working version";
void smooth(int dim, pixel *src, pixel *dst) 
{
    int i, j, ii, jj, red, blue, green, cPixel;
    int dim1 = dim - 1;
    int dim2 = dim - 2;
    
    // Top row//
    // Top left pixel//
    
    i = 0;
    j = 0;
    red = blue = green = 0;
    ii = 0;
    jj = 0;
    cPixel = (ii*dim + jj);
    red += src[cPixel].red;
    green += src[cPixel].green;
    blue += src[cPixel].blue;
    jj = 1;
    cPixel = (ii*dim + jj);
    red += src[cPixel].red;
    green += src[cPixel].green;
    blue += src[cPixel].blue;
    ii = 1
    jj = 0;
    cPixel = (ii*dim + jj);
    red += src[cPixel].red;
    green += src[cPixel].green;
    blue += src[cPixel].blue;
    jj = 1;
    cPixel = (ii*dim + jj);
    red += src[cPixel].red;
    green += src[cPixel].green;
    blue += src[cPixel].blue;
    
    
    cPixel = (i*dim + j);
    dst[cPixel].red = red/2;
    dst[cPixel].green = green/2;
    dst[cPixel].blue = blue/2;
    
    // Top row - middle pixel//
    
    for (j = 1; j <= dim2; j++){
    red = blue = green = 0;
    for(ii = 0; ii <= 1; ii++){
    for (jj = j-1; jj <= j +1; jj++){
    cPixel = (ii*dim + jj);
    red += src[cPixel].red;
    green += src[cPixel].green;
    blue += src[cPixel].blue;
   }
 }  
    
    cPixel = (i*dim + j);
    dst[cPixel].red = red/6;
    dst[cPixel].green = green/6;
    dst[cPixel].blue = blue/6;
}

     // Top right pixel//
     
     for (j = dim1; j <= dim1; j++){
     red = blue = green = 0;
       for(ii = 0; ii <= 1; ii++){
         for (jj = dim2; jj <= dim1; jj++){
           cPixel = (ii*dim + jj);
           red += src[cPixel].red;
           green += src[cPixel].green;
           blue += src[cPixel].blue;
           jj++;
           
           cPixel = (ii*dim + jj);
           red += src[cPixel].red;
           green += src[cPixel].green;
           blue += src[cPixel].blue;
     }
   }       

         cPixel = (i*dim + j);
         dst[cPixel].red = red/2;
         dst[cPixel].green = green/2;
         dst[cPixel].blue = blue/2;
   }      
        
        
        // Middle row//
        
        // Middle pixel on the left//
        
         for (i = 1; i <= dim2; i++({
         for (j = 0; j < 1; j++){
         red = blue = green = 0;
         for(ii = i - 1; ii <= i + 1; ii++){
         for (jj = 0; jj <= 1; jj++){
         cPixel = (ii*dim + jj);
         red += src[cPixel].red;
         green += src[cPixel].green;
         blue += src[cPixel].blue;
       }
 }
          cPixel = (i*dim + j);
          dst[cPixel].red = red/6;
          dst[cPixel].green = green/6;
          dst[cPixel].blue = blue/6;
    }
    

    // Middle pixels//
    
    for (j = 1; j <= dim2; j++){
    red = blue = green = 0;
    for(ii = i - 1; ii <= i + 1; ii++){
    for (jj = j-1; jj <= j +1; jj++){
    cPixel = (ii*dim + jj);
    red += src[cPixel].red;
    green += src[cPixel].green;
    blue += src[cPixel].blue;
  }    
}
    cPixel = (i*dim + j);
    dst[cPixel].red = red/9;
    dst[cPixel].green = green/9;
    dst[cPixel].blue = blue/9;
    } 

// Middle pixel on the right//
    
    for (j = dim1; j <= dim1; j++){
     red = blue = green = 0;
       for(ii = i - 1; ii <= i + 1; ii++){
         for (jj = dim2; jj <= dim1; jj++){
           cPixel = (ii*dim + jj);
           red += src[cPixel].red;
           green += src[cPixel].green;
           blue += src[cPixel].blue;
        }
    }

         cPixel = (i*dim + j);
         dst[cPixel].red = red/6;
         dst[cPixel].green = green/6;
         dst[cPixel].blue = blue/6;
      }
   }      

   // Bottom row//
   // Bottom pixel on the left//
   
   for (i = dim1; i <= dim1; i++){
   for (j = 0; j < 1; j++){
     red = blue = green = 0;
       for(ii = dim2; ii <= dim1; ii++){
         for (jj = 0; jj <= 1; jj++){
           cPixel = (ii*dim + jj);
           red += src[cPixel].red;
           green += src[cPixel].green;
           blue += src[cPixel].blue;
        }
  }
         cPixel = (i*dim + j);
         dst[cPixel].red = red/2;
         dst[cPixel].green = green/2;
         dst[cPixel].blue = blue/2;
   }
   
   // Bottom row - middle pixel//
   
    for (j = 1; j <= dim2; j++){
    red = blue = green = 0;
    for(ii = dim2; ii <= dim ; ii++){
    for (jj = j-1; jj <= j +1; jj++){
    cPixel = (ii*dim + jj);
    red += src[cPixel].red;
    green += src[cPixel].green;
    blue += src[cPixel].blue;
   }    
 }
    cPixel = (i*dim + j);
    dst[cPixel].red = red/6;
    dst[cPixel].green = green/6;
    dst[cPixel].blue = blue/6;
  }
      
   // Bottom right pixel//
   
   for (j = dim1; j <= dim1; j++){
     red = blue = green = 0;
       for(ii = dim2; ii <= dim1; ii++){
         for (jj = dim2; jj <= dim1; jj++){
           cPixel = (ii*dim + jj);
           red += src[cPixel].red;
           green += src[cPixel].green;
           blue += src[cPixel].blue;
        }
  }
         cPixel = (i*dim + j);
         dst[cPixel].red = red/2;
         dst[cPixel].green = green/2;
         dst[cPixel].blue = blue/2;
   }
}

   
/********************************************************************* 
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_smooth_functions() {
    add_smooth_function(&smooth, smooth_descr);
    add_smooth_function(&naive_smooth, naive_smooth_descr);
    /* ... Register additional test functions here */
}

