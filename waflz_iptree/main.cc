#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <getopt.h>
#include <time.h>
#include <algorithm>
#include "nms.h"

#define MAX_READLINE_SIZE 1024
#ifndef STATUS_OK
#define STATUS_OK 0
#endif
#ifndef STATUS_ERROR
#define STATUS_ERROR -1
#endif

//: ----------------------------------------------------------------------------
//: \details:  TODO
//: \return:   TODO
//: \param:    TODO
//: ----------------------------------------------------------------------------
void print_usage(FILE* a_stream, int a_exit_code)
{
        fprintf(a_stream, "Usage: ip_tree [OPTIONS]\n");
        fprintf(a_stream, "msc ip Tree Test.\n");
        fprintf(a_stream, "\n");
        fprintf(a_stream, "OPTIONS:\n");
        fprintf(a_stream, "  -h, --help       Display this help and exit.\n");
        fprintf(a_stream, "  -f, --file       Input file containinf ip's to load.\n");
        fprintf(a_stream, "  -s, --search     Input file containing ip's to search\n");
        exit(a_exit_code);
}
//: ----------------------------------------------------------------------------
//:
//: ----------------------------------------------------------------------------
int main(int argc, char** argv)
{
         int32_t l_s = STATUS_OK;
        // -----------------------------------------
        // process args
        // -----------------------------------------
         char l_opt;
         std::string l_arg;
         std::string l_file_load_str;
         std::string l_file_search_str;
         int l_option_index = 0;
         //char* l_search_ip = NULL;
        //uint32_t l_size;

         struct option l_long_options[] = 
                {
                {"help",        0, 0, 'h'},
                {"file",        1, 0, 'f'},
                {"search",      1, 0, 's'},
                {0, 0, 0, 0}
                };

        while ((l_opt = getopt_long_only(argc, argv, "hf:s:", l_long_options, &l_option_index)) != -1)
        {
                if (optarg)
                {
                    l_arg = optarg;
                }

                switch(l_opt)
                {
                // -----------------------------------------
                // help
                // -----------------------------------------
                case 'h':
                {
                        print_usage(stdout, 0);
                        break;
                }
                // -----------------------------------------
                //  file containing ip's to load
                // -----------------------------------------
                case 'f':
                {
                        l_file_load_str = l_arg;
                        break;
                }
                // -----------------------------------------
                //  file containing ip's to search
                // ----------------------------------------
                case 's':
                {
                        l_file_search_str = l_arg;
                        break;
                }
                default:
                {
                        fprintf(stdout, "unrecognized option");
                        print_usage(stdout, -1);
                        break;

                }
                }
        }

        if(l_file_load_str.empty())
        {
                printf("please provide input file with ip's to load");
                print_usage(stdout, -1);
        }
        // -----------------------------------------
        //  load ip's
        // ----------------------------------------- 
        FILE * l_fp;
        l_fp = fopen(l_file_load_str.c_str(),"r");
        if (NULL == l_fp)
        {
               printf("Error opening file: %s.  Reason: %s\n", l_file_load_str.c_str(), strerror(errno));
               return STATUS_ERROR;
        }
        ns_waflz::nms* l_nms = NULL;
        l_s = ns_waflz::create_nms_from_file(&l_nms, l_file_load_str);
        if(l_s == STATUS_OK)
        {
        	 printf("ip loaded succesfully\n");
        }
        else
        {
            printf("loading ip failed\n");
            if(l_nms != NULL) { delete l_nms; l_nms = NULL; }
            return 0;
        }
        // -----------------------------------------
        //  load ip's
        // ----------------------------------------- 
        if(l_file_search_str.empty())
        {
                if(l_nms != NULL) { delete l_nms; l_nms = NULL; }
                return 0;
        }

        printf("Searching\n");
        double l_total_time;
        clock_t l_start, l_end;
        bool ao_output = false;

        l_fp = fopen(l_file_search_str.c_str(), "r");
        if(NULL == l_fp)
        {
                printf("Error opening file: %s. Reason: %s\n", l_file_search_str.c_str(), strerror(errno));
                return STATUS_ERROR;
        }
        char l_rline[MAX_READLINE_SIZE];
        l_start = clock();
        while(fgets(l_rline, sizeof(l_rline), l_fp))
        {
                size_t l_rline_len = strnlen(l_rline, MAX_READLINE_SIZE);
                if(!l_rline_len)
                {
                        continue;
                }
                else if(l_rline_len == MAX_READLINE_SIZE)
                {
                        if(l_nms) { delete l_nms; l_nms = NULL;}
                        return STATUS_ERROR;
                }
                // nuke endline
                l_rline[l_rline_len - 1] = '\0';
                std::string l_line(l_rline);
                l_line.erase( std::remove_if( l_line.begin(), l_line.end(), ::isspace ), l_line.end() );
                if(l_line.empty())
                {
                        continue;
                }
                l_s = l_nms->contains(ao_output, l_line.c_str(), l_line.length());
                if(ao_output)
                {
                    printf("%d\n", ao_output);
                }
        }
        l_end = clock();
        l_total_time = ((double)(l_end-l_start)) / CLOCKS_PER_SEC;
        printf("time taken to search:%f\n", l_total_time);
                
cleanup:
        if(l_nms != NULL)
        {
            delete l_nms;
            l_nms = NULL;
        }    
        return 0;
}
