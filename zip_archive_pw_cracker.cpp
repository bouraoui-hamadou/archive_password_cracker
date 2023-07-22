/*-
 * Your Educational Code
 * ZIP Archive Password Cracker
 * This C++ program uses the libarchive library to crack encrypted ZIP archives. 
 * It tries all possible combinations of characters to find the correct password. 
 * The console displays each attempt, and if successful, it extracts the files. 
 * The program tracks attempts, elapsed time, and displays results. 
 * Remember to use responsibly and ethically. Unauthorized access is illegal.
 *
 * Copyright (c) [2023] [Bouraoui Hamadou]
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR(S) "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR(S) BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include <iostream>
#include <fstream>
#include <coroutine>
#include <optional>
#include <vector>
#include "CombinationGenerator.hpp"
#include <archive.h>
#include <archive_entry.h>
#include <chrono>

using namespace std::chrono;

int main(){
    const std::string zipFilePath = "data/dummy_file.zip"; // Path to the zip archive

    struct archive *a;
    struct archive_entry *entry;
    int r;
    int pw_length = 6;
    

    std::vector<char> characters = {'_', '+','i', 'u', '#'};
    
    CombinationGenerator pw_generator = combinations(characters, pw_length);
    std::string password = "";
    bool found = false;
    unsigned long int nb_combinations = 0;

    
    auto start = high_resolution_clock::now();
    while(!found && pw_generator.move_next()){
        nb_combinations++;
        // Step 1: Create an archive read handle
        a = archive_read_new();
        archive_read_support_format_zip(a);
        
        std::vector<char> pw_combination = pw_generator.current_value();
        pw_combination.push_back('\0');
        const char* cstr = pw_combination.data();
        std::cout<<cstr<<'\r'<<std::flush;
        
        // Step 2: Set the password for the encrypted archive     
        archive_read_add_passphrase(a, cstr);
            
        
        // Step 3: Open the archive file
        r = archive_read_open_filename(a, zipFilePath.c_str(), 10240); // 10240 is the read buffer size
        
        if(r != ARCHIVE_OK){    
            a = archive_read_new();
            archive_read_support_format_zip(a);
            archive_read_add_passphrase(a, cstr);
            continue;
        }

        // Step 4: Iterate through the entries in the archive and extract each file
        while(archive_read_next_header(a, &entry) == ARCHIVE_OK){
            const char *entryPath = archive_entry_pathname(entry);
            r = archive_read_extract(a, entry, ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_SECURE_SYMLINKS);
            if (r!=ARCHIVE_OK){
                archive_read_add_passphrase(a, cstr);
                continue;
            }
            else{
                found = true;
                std::cout<<"Found password: "<<cstr<<std::endl;
            }
        }
        
    }

    auto stop = high_resolution_clock::now();
  
    

    // Step 5: Close the archive
    archive_read_close(a);
    archive_read_free(a);

    auto duration = duration_cast<milliseconds> (stop - start);
    std::cout<<"Extraction completed successfully!"<<"\t found= "<<found<<"\nElapsed time in ms:\n"<<duration.count()
    <<"\nNumber of tested combinations\n"<<nb_combinations<<std::endl;
    return 0;
}
