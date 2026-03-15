bool Strstr(char* str, char* sub_str)
{
    if (strlen(sub_str) > strlen(str))
        return false; // sub_str is longer than str

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == sub_str[0]) {
            for (int j = 0; sub_str[j] != '\0'; j++)
            {
                if (str[i + j] != sub_str[j]) {
                    break; // mismatch found
                }
                if (sub_str[j + 1] == '\0') {
                    return true; // found the substring
                }
            }
        }
    }
    return false;
}

int Strstr_index(char* str, char* sub_str)
{
    if (strlen(sub_str) > strlen(str))
        return -1; // sub_str is longer than str

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == sub_str[0]) {
            for (int j = 0; sub_str[j] != '\0'; j++)
            {
                if (str[i + j] != sub_str[j]) {
                    break; // mismatch found
                }
                if (sub_str[j + 1] == '\0') {
                    return i; // found the substring
                }
            }
        }
    }
    return -1; // substring not found
}

void ToLower(char* str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] += 32; // convert to lowercase
        }
    }
}

void Strcat(char* dest, const char* src)
{
    int dest_len = strlen(dest);
    int src_len = strlen(src);

    for (int i = 0; i < src_len; i++)
    {
        dest[dest_len + i] = src[i];
    }
    dest[dest_len + src_len] = '\0'; // null-terminate the destination string
}

void Strncat(char* dest, const char* src, int n)
{
    int dest_len = strlen(dest);
    if (n < 0) {
        n = 0; // if n is negative, set it to 0
    } if (n > strlen(src)) {
        n = strlen(src); // if n is greater than src length, adjust it
    }

    for (int i = 0; i < n && src[i] != '\0'; i++)
    {
        dest[dest_len + i] = src[i];
    }
    dest[dest_len + n] = '\0'; // null-terminate the destination string
}

void Strcpy(char* dest, const char* src)
{
    int i = 0;
    do {
        dest[i] = src[i];
        i++;
    } while (src[i - 1] != '\0'); // copy until null terminator
    dest[i] = '\0'; // null-terminate the destination string
}
