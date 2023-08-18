#ifndef PM_FILES_H
#define PM_FILES_H

/// <summary>
/// Opens a file, reads the contents into a string array, and closes the file.
/// </summary>
char** pm_fs_read_lines(const char* path);

/// <summary>
/// Opens a file, reads the contents into a string, and closes the file.
/// </summary>
char* pm_fs_read_text(const char* path);

#endif // PM_FILES_H
