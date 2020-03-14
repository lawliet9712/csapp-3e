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
    "lab killer",              /* Team name */

    "Harry Q. Bovik",     /* First member full name */
    "bovik@nowhere.edu",  /* First member email address */

    "lawliet",                   /* Second member full name (leave blank if none) */
    "lawliet@163.com"            /* Second member email addr (leave blank if none) */
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

int block_size = 32;
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
}

char effective_rotate_descr[] = "effective_rotate: effective baseline implementation";
void effective_rotate(int dim, pixel *src, pixel *dst) 
{
    int i, x;
    pixel * dst_tmp = dst, * src_tmp = src;
    dst_tmp += RIDX(dim-1, 0, dim);

    for (i = 0; i < dim; i+=32)
    {
        for (x = 0; x < dim; x++)
            {
                *dst_tmp = *src_tmp; dst_tmp++; src_tmp+=dim;
                *dst_tmp = *src_tmp; dst_tmp++; src_tmp+=dim;
                *dst_tmp = *src_tmp; dst_tmp++; src_tmp+=dim;
                *dst_tmp = *src_tmp; dst_tmp++; src_tmp+=dim;
                *dst_tmp = *src_tmp; dst_tmp++; src_tmp+=dim;
                *dst_tmp = *src_tmp; dst_tmp++; src_tmp+=dim;
                *dst_tmp = *src_tmp; dst_tmp++; src_tmp+=dim;
                *dst_tmp = *src_tmp; dst_tmp++; src_tmp+=dim;
                *dst_tmp = *src_tmp; dst_tmp++; src_tmp+=dim;
                *dst_tmp = *src_tmp; dst_tmp++; src_tmp+=dim;
                *dst_tmp = *src_tmp; dst_tmp++; src_tmp+=dim;
                *dst_tmp = *src_tmp; dst_tmp++; src_tmp+=dim;
                *dst_tmp = *src_tmp; dst_tmp++; src_tmp+=dim;
                *dst_tmp = *src_tmp; dst_tmp++; src_tmp+=dim;
                *dst_tmp = *src_tmp; dst_tmp++; src_tmp+=dim;
                *dst_tmp = *src_tmp; dst_tmp++; src_tmp+=dim;
                *dst_tmp = *src_tmp; dst_tmp++; src_tmp+=dim;
                *dst_tmp = *src_tmp; dst_tmp++; src_tmp+=dim;
                *dst_tmp = *src_tmp; dst_tmp++; src_tmp+=dim;
                *dst_tmp = *src_tmp; dst_tmp++; src_tmp+=dim;
                *dst_tmp = *src_tmp; dst_tmp++; src_tmp+=dim;
                *dst_tmp = *src_tmp; dst_tmp++; src_tmp+=dim;
                *dst_tmp = *src_tmp; dst_tmp++; src_tmp+=dim;
                *dst_tmp = *src_tmp; dst_tmp++; src_tmp+=dim;
                *dst_tmp = *src_tmp; dst_tmp++; src_tmp+=dim;
                *dst_tmp = *src_tmp; dst_tmp++; src_tmp+=dim;
                *dst_tmp = *src_tmp; dst_tmp++; src_tmp+=dim;
                *dst_tmp = *src_tmp; dst_tmp++; src_tmp+=dim;
                *dst_tmp = *src_tmp; dst_tmp++; src_tmp+=dim;
                *dst_tmp = *src_tmp; dst_tmp++; src_tmp+=dim;
                *dst_tmp = *src_tmp; dst_tmp++; src_tmp+=dim;
                *dst_tmp = *src_tmp; 

                src_tmp = src_tmp - (dim << 5) + dim + 1;
                dst_tmp = dst_tmp - 31 - dim;
            }
        src_tmp = src_tmp + (dim << 5) - dim;
        dst_tmp = dst_tmp + dim * dim + 32;
    }
}

#if 0
                dst[RIDX(dim-1-y, x, dim)]  = src[RIDX(x, y, dim)];
                dst[RIDX(dim-1-y-1, x, dim)]  = src[RIDX(x, y+1, dim)];
                dst[RIDX(dim-1-y-2, x, dim)]  = src[RIDX(x, y+2, dim)];
                dst[RIDX(dim-1-y-3, x, dim)]  = src[RIDX(x, y+3, dim)];

                dst[RIDX(dim-1-y, x+1, dim)]  = src[RIDX(x+1, y, dim)];
                dst[RIDX(dim-1-y-1, x+1, dim)]  = src[RIDX(x+1, y+1, dim)];
                dst[RIDX(dim-1-y-2, x+1, dim)]  = src[RIDX(x+1, y+2, dim)];
                dst[RIDX(dim-1-y-3, x+1, dim)]  = src[RIDX(x+1, y+3, dim)];

                dst[RIDX(dim-1-y, x+2, dim)]  = src[RIDX(x+2, y, dim)];
                dst[RIDX(dim-1-y-1, x+2, dim)]  = src[RIDX(x+2, y+1, dim)];
                dst[RIDX(dim-1-y-2, x+2, dim)]  = src[RIDX(x+2, y+2, dim)];
                dst[RIDX(dim-1-y-3, x+2, dim)]  = src[RIDX(x+2, y+3, dim)];

                dst[RIDX(dim-1-y, x+3, dim)]  = src[RIDX(x+3, y, dim)];
                dst[RIDX(dim-1-y-1, x+3, dim)]  = src[RIDX(x+3, y+1, dim)];
                dst[RIDX(dim-1-y-2, x+3, dim)]  = src[RIDX(x+3, y+2, dim)];
                dst[RIDX(dim-1-y-3, x+3, dim)]  = src[RIDX(x+3, y+3, dim)];
#endif
/* 
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr[] = "rotate: Current working version";
void rotate(int dim, pixel *src, pixel *dst) 
{
    //naive_rotate(dim, src, dst);
    effective_rotate(dim, src, dst);
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
    //add_rotate_function(&naive_rotate, naive_rotate_descr);   
    add_rotate_function(&rotate, rotate_descr);   
    //add_rotate_function(&effective_rotate, test_rotate_descr);   
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

    // 初始化 0
    // 该函数本质上就是将像素点的周围像素点求和取平均值，再赋值给该像素点
    // 可以考虑将特殊情况的像素点的值求出来, 然后剩下的再用分块的方法求值
    // @note : 不能改变原来数组的值
    initialize_pixel_sum(&sum);
    for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++) 
	for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++) 
        // 累加到 sum
	    accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);

    // sum 赋值, 赋值前的除法或许可以换成逻辑右移
    // 返回又有拷贝赋值
    assign_sum_to_pixel(&current_pixel, sum);
    return current_pixel;
}

static void effective_avg(int dim, int i, int j, pixel *src, pixel *dst) 
{
    int ii, jj;
    pixel_sum sum;

    // 初始化 0
    // 该函数本质上就是将像素点的周围像素点求和取平均值，再赋值给该像素点
    // 可以考虑将特殊情况的像素点的值求出来, 然后剩下的再用分块的方法求值
    // @note : 不能改变原来数组的值
    initialize_pixel_sum(&sum);
    for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++) 
	for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++) 
        // 累加到 sum
	    accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);

    // sum 赋值, 赋值前的除法或许可以换成逻辑右移
    assign_sum_to_pixel(dst, sum);
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

char effective_smooth_descr[] = "effective_smooth: effective baseline implementation";
void effective_smooth(int dim, pixel *src, pixel *dst) 
{
    int i, j;
    // 处理左上角的像素点
    dst[0].red = (src[0].red + src[1].red + src[dim + 1].red + src[dim].red) >> 2;
    dst[0].blue = (src[0].blue + src[1].blue + src[dim + 1].blue + src[dim].blue) >> 2;
    dst[0].green = (src[0].green + src[1].green + src[dim + 1].green + src[dim].green) >> 2;
    
    // 处理右上角的像素点
    int dim_mul_2 = dim << 1;
    dst[dim-1].red = (src[dim-1].red + src[dim-2].red + src[dim_mul_2 - 2].red + src[dim_mul_2 - 1].red) >> 2; 
    dst[dim-1].blue = (src[dim-1].blue + src[dim-2].blue + src[dim_mul_2 - 2].blue + src[dim_mul_2 - 1].blue) >> 2; 
    dst[dim-1].green = (src[dim-1].green + src[dim-2].green + src[dim_mul_2 - 2].green + src[dim_mul_2 - 1].green) >> 2; 

    //int power_of_two = 4; 
    //while ((dim >> (++power_of_two)) != 1);
    
    // 处理左下角的像素点
    int bottom_first_elem = dim * (dim - 1);//(dim << power_of_two) - dim; // 
    dst[bottom_first_elem].red = (src[bottom_first_elem].red + src[bottom_first_elem + 1].red + src[bottom_first_elem - dim].red + src[bottom_first_elem - dim + 1].red) >> 2;
    dst[bottom_first_elem].blue = (src[bottom_first_elem].blue + src[bottom_first_elem + 1].blue + src[bottom_first_elem - dim].blue + src[bottom_first_elem - dim + 1].blue) >> 2;
    dst[bottom_first_elem].green = (src[bottom_first_elem].green + src[bottom_first_elem + 1].green + src[bottom_first_elem - dim].green + src[bottom_first_elem - dim + 1].green) >> 2;

    // 处理右下角的像素点
    int bottom_last_elem =  dim * dim - 1;//(dim << power_of_two) - 1; // equal dim * dim - 1
    dst[bottom_last_elem].red = (src[bottom_last_elem].red + src[bottom_last_elem - 1].red + src[bottom_last_elem - dim].red + src[bottom_last_elem - dim - 1].red ) >> 2;
    dst[bottom_last_elem].blue = (src[bottom_last_elem].blue + src[bottom_last_elem - 1].blue + src[bottom_last_elem - dim].blue + src[bottom_last_elem - dim - 1].blue) >> 2;
    dst[bottom_last_elem].green = (src[bottom_last_elem].green + src[bottom_last_elem - 1].green + src[bottom_last_elem - dim].green + src[bottom_last_elem - dim - 1].green) >> 2;

    // 处理第一行
    for (i = 1; i < dim - 1; i++)
    {
        dst[i].red = (src[i].red + src[i-1].red + src[i-1+dim].red + src[i+dim].red + src[i+1].red + src[i+1+dim].red) / 6;
        dst[i].blue = (src[i].blue + src[i-1].blue + src[i-1+dim].blue + src[i+dim].blue + src[i+1].blue + src[i+1+dim].blue) / 6;
        dst[i].green = (src[i].green + src[i-1].green + src[i-1+dim].green + src[i+dim].green + src[i+1].green + src[i+1+dim].green) / 6;
    }

    // 处理最后一行
    for (i = bottom_first_elem + 1; i < bottom_last_elem; i++)
    {
        dst[i].red = (src[i].red + src[i-1].red + src[i-1-dim].red + src[i-dim].red + src[i+1].red + src[i+1-dim].red) / 6;
        dst[i].blue = (src[i].blue + src[i-1].blue + src[i-1-dim].blue + src[i-dim].blue + src[i+1].blue + src[i+1-dim].blue) / 6;
        dst[i].green = (src[i].green + src[i-1].green + src[i-1-dim].green + src[i-dim].green + src[i+1].green + src[i+1-dim].green) / 6;
    }

    // 处理第一列
    for (i = dim; i < bottom_first_elem; i+=dim)
    {
        dst[i].red = (src[i].red + src[i-dim].red + src[i+1-dim].red + src[i+1].red + src[i+1+dim].red + src[i+dim].red) / 6;
        dst[i].blue = (src[i].blue + src[i-dim].blue + src[i+1-dim].blue + src[i+1].blue + src[i+1+dim].blue + src[i+dim].blue) / 6;
        dst[i].green = (src[i].green + src[i-dim].green + src[i+1-dim].green + src[i+1].green + src[i+1+dim].green + src[i+dim].green) / 6;
    }
    
    // 处理最后一列
    for (i = dim_mul_2 - 1; i < bottom_last_elem; i+=dim)
    {
        dst[i].red = (src[i].red + src[i-dim].red + src[i-1-dim].red + src[i-1].red + src[i-1+dim].red + src[i+dim].red) / 6;
        dst[i].blue = (src[i].blue + src[i-dim].blue + src[i-1-dim].blue + src[i-1].blue + src[i-1+dim].blue + src[i+dim].blue) / 6;
        dst[i].green = (src[i].green + src[i-dim].green + src[i-1-dim].green + src[i-1].green + src[i-1+dim].green + src[i+dim].green) / 6;
    }

    // 处理中心区域, 考虑分块
    for (i = dim; i < bottom_first_elem; i+=dim)
        for (j = 1; j < dim - 1; j++)
        {
            dst[i+j].red = (src[i+j].red + src[i+j-1].red + src[i+j+1].red + src[i+j-dim].red + src[i+j+dim].red + src[i+j-dim-1].red + src[i+j-dim+1].red + src[i+j+dim-1].red + src[i+j+dim+1].red) / 9;
            dst[i+j].blue = (src[i+j].blue +src[i+j-1].blue + src[i+j+1].blue + src[i+j-dim].blue + src[i+j+dim].blue + src[i+j-dim-1].blue + src[i+j-dim+1].blue + src[i+j+dim-1].blue + src[i+j+dim+1].blue) / 9;
            dst[i+j].green = (src[i+j].green + src[i+j-1].green + src[i+j+1].green + src[i+j-dim].green + src[i+j+dim].green + src[i+j-dim-1].green + src[i+j-dim+1].green + src[i+j+dim-1].green + src[i+j+dim+1].green) / 9;
        }
}

/*
 * smooth - Your current working version of smooth. 
 * IMPORTANT: This is the version you will be graded on
 */
char smooth_descr[] = "smooth: Current working version";
void smooth(int dim, pixel *src, pixel *dst) 
{
    //naive_smooth(dim, src, dst);
    effective_smooth(dim, src, dst);
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

