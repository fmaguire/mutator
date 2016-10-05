#include <iostream>
#include <fstream>
#include <string.h>
#include <cstdlib>
#include <random>

int main (int argc, char *argv[]) {

    // Check CLI arg input 
    if(argc != 5 || strcmp(argv[1], "-h") == 0) {

        std::cout << "Usage: " << argv[0] << " in.fq mutated.fq total_bases proportion" << '\n';
        std::cout << "Count bases via 'cat in.fq | paste - - - - | awk -F '\t' '{print $2}' | wc -c" << '\n';
        std::exit(1);
    }
    // Parse CLI arguments
    char* in_fn = argv[1];
    char* out_fn = argv[2]; 
    float bases = atof(argv[3]);
    float prop = atof(argv[4]);

    // initialise vars for reading input files and open them
    std::string curr_line;
    std::ifstream in_fp;
    std::ofstream out_fp;
    
    // open files
    in_fp.open(in_fn);
    out_fp.open(out_fn);
    
    // character alphabet
    char alphabet[] = "AGTC";

    
    // initialise vars for main loop
    unsigned int line_number = 0;

    //prob of change
    float pr = (prop * bases) / bases;

    // generator for randint to tell which base to incorporate
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,3);
    
    // change counter
    int changes = 0;
     
    if(in_fp.is_open() && out_fp.is_open()){
        std::cout << "Mutating" << "\n";
        
        while(std::getline(in_fp, curr_line)){
            
            line_number++;

            // As files are fastq only every 4N+2, N>=0 lines contain sequences
            if(line_number % 4 == 2){
                
                // ignore first 5bp
                // randomly introduce error at varying thresholds
                // 0.1% of bases  entire sequence 
                //
                //  pr(change) = E(0.001*base)   1c
                // float change = 0.001*bases / bases 
                // randint(0,1) 
                // if(randint(0,1) >= change){
                //      
                //   char nt = ALPHABET[randint(0,4)];
                // }
                curr_line = curr_line;

                for(int i = 0; i < 95; i++){

                    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                        //std::cout << r << '\n';

                        if ( r <= pr ) {
                            changes++;
                            int dice_roll = distribution(generator);
                            curr_line[i] = alphabet[dice_roll];
                        }
                }

            }

            out_fp << curr_line << "\n";
        }

    } else {
        std::cout << "Problem opening files" << '\n';
        exit(1);
    }
    
    in_fp.close();
    out_fp.close();
    
    float prop_changes = (float)(changes) / bases;
    std::cout << "Total bases changed = " << changes << "\n";
    std::cout << "Proportion changed = " << prop_changes << "\n";

    return 0;
}
