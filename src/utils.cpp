#include "utils.h"

struct PathSDInfo {
    String tree_str;
    String pwd;
};

PathSDInfo cleanSD_(PathSDInfo sd_info){
/* Auxiliary to deleted all SD files
 * Input:
 *     - [PathSDInfo]: Current folder and files (not) removed so far
 * Output:
 *     - [PathSDInfo]: Current folder and files (not) removed so far
 */
    // Root
    PathSDInfo sd_info_cp = sd_info;

    File dir = SD.open(sd_info_cp.pwd);
    File nextdir = dir.openNextFile();

    while(nextdir) {
        String filepath;

        if(sd_info_cp.tree_str == "/"){
            sd_info_cp.tree_str = "";
        }

        if (nextdir.isDirectory()) {
            filepath =  sd_info.pwd + nextdir.name() + "/";
            sd_info_cp.pwd = filepath;
            sd_info_cp = cleanSD_(sd_info_cp);

            sd_info_cp.pwd = sd_info.pwd;
            sd_info_cp.tree_str += SD.rmdir(filepath) ? "Removed dir       : " + filepath + "\n":
                                                        "Not Removed dir   : " + filepath + "\n";

        } else { 
            filepath = sd_info.pwd + nextdir.name();
            sd_info_cp.tree_str += SD.remove(filepath) ? "Removed file     : " + filepath + "\n":
                                                         "Not removed file : " + filepath + "\n";
        }
 
        nextdir =  dir.openNextFile();
    }

    return sd_info_cp;
}

String cleanSD(int pin, String address){
/* List SD file's content
 * Input:
 *     - [String]: Raiz do cartao ou pasta neste
 * Saida:
 *     -
 */
    SD.begin(pin);
    PathSDInfo sd_info{address, address};
    sd_info = cleanSD_(sd_info);
    return sd_info.tree_str;   
}

PathSDInfo listSD_(PathSDInfo sd_info) {
/* Auxiliary for list of SD file's content
 * Input:
 *     - [PathSDInfo]: Current directory and file tree
 * Output:
 *     - [PathSDInfo]: Current directory and file tree
 *     with (not) deleted files
 */
    PathSDInfo sd_info_cp = sd_info;

    File dir = SD.open(sd_info_cp.pwd);
    File nextdir = dir.openNextFile();
    
    sd_info_cp.tree_str += "\n";

    while(nextdir) {
        if (nextdir.isDirectory()) {
            sd_info_cp.tree_str += sd_info_cp.pwd + nextdir.name() + "/";
            sd_info_cp.pwd += nextdir.name() + String("/");

            sd_info_cp = listSD_(sd_info_cp);
        } else {
            sd_info_cp.tree_str += sd_info_cp.pwd + nextdir.name() + "\n";
        }

        sd_info_cp.pwd = sd_info.pwd;
        nextdir =  dir.openNextFile();
    }

    dir.close();
    nextdir.close();

    return sd_info_cp;
}

String listSD(int pin, String address) {
/* List SD file's content
 * Input:
 *     - [String]: Raiz do cartao ou pasta neste
 * Saida:
 *     -
 */
    SD.begin(pin);
    PathSDInfo sd_info{address, address};
    sd_info = listSD_(sd_info);
    return sd_info.tree_str;   
}
