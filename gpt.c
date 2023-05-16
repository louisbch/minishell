#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_env
{
    char            *name;
    char            *value;
    struct s_env    *next;
} t_env;

char *get_value_from_linked_list(t_env *env_list, const char *name)
{
    while (env_list != NULL)
    {
        if (strcmp(env_list->name, name) == 0)
            return env_list->value;
        env_list = env_list->next;
    }
    return NULL;  // Value not found
}

void replace_word_with_value(t_env *env_list, char *str)
{
    char *dollar = ft_strchr(str, '$');
    while (dollar != NULL)
    {
        char *word_start = dollar + 1;
        char *word_end = strpbrk(word_start, " \t\n\r\f\v$");
        if (word_end == NULL)
            word_end = word_start + strlen(word_start);

        size_t word_length = word_end - word_start;
        if (word_length > 0)
        {
            char *word = malloc(word_length + 1);
            strncpy(word, word_start, word_length);
            word[word_length] = '\0';

            char *value = get_value_from_linked_list(env_list, word);
            if (value != NULL)
            {
                size_t value_length = strlen(value);
                size_t replacement_length = strlen(str) - word_length + value_length;

                char *replacement = malloc(replacement_length + 1);
                strncpy(replacement, str, dollar - str);
                replacement[dollar - str] = '\0';
                strcat(replacement, value);
                strcat(replacement, word_end);

                strcpy(str, replacement);
                free(replacement);
            }

            free(word);
        }

        dollar = strchr(dollar + 1, '$');
    }
}

int main()
{
    // Example usage
    t_env *env_list = malloc(sizeof(t_env));
    env_list->name = "foo";
    env_list->value = "bar";
    env_list->next = NULL;

    char str[100] = "This is a $foo example.";

    replace_word_with_value(env_list, str);

    printf("%s\n", str);  // Output: "This is a bar example."

    return 0;
}
