#ifndef TEMP_FILE_H
#define TEMP_FILE_H

/* Create temp file from source text
   Returns 0 on success
   Returns -1 on failure
*/
int temp_file_create(const char *source_path);

/* Get temp file path */
const char *temp_file_path(void);

/* Delete temp file safely */
void temp_file_cleanup(void);

#endif
