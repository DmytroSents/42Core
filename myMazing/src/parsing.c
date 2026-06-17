#include "utils.h"

int txt_to_struct(int argc, char *argv[], t_param *p)
{
    if (argc != 2)
        return (write(1, "Wrong, Bro!\n", strlen("Wrong, Bro!\n")) * -1);

    FILE *config_ft = fopen(argv[1], "r");
    if (!config_ft)
        return (perror("fopen"), -1);

    static char txt_buff[BUFFER_SIZE] = {0};

    while (fgets(txt_buff, sizeof(txt_buff), config_ft))
    {
        size_t len = strlen(txt_buff);

        	// IF line too long: buffer filled AND \n doesn't fit in.
        if (len == sizeof(txt_buff) - 1 && txt_buff[len - 1] != '\n')
        {
            printf("Stop jerking my config file, psycho!\n");
            fclose(config_ft);
            return (-1);
        }

        if (process_line(p, txt_buff) < 0)
        {
            fclose(config_ft);
            return (-1);
        }
    }

    if (fclose(config_ft) != 0)
        return (perror("fclose"), -1);
	   // ↑↑↑ This is not mine, but it's needed (probably)
    return (0);
}

int process_line(t_param *params, char *buffer)
{
	char *key_str = buffer;

	while (*key_str == ' ' || *key_str == '\t')
        key_str++;

    if (!(*key_str) || *key_str == '#' || *key_str == '\n')
        return (0);

    if (strcasestr(key_str, "WIDTH") && params->width <= 0)
        return (process_int(params, key_str, 'w'));
    else if (strcasestr(key_str, "HEIGHT") && params->height <= 0)
        return (process_int(params, key_str, 'h'));
    else if (strcasestr(key_str, "EXIT") && params->exit[0] <= 0)
        return (process_int(params, key_str, 'x'));
    else if (strcasestr(key_str, "ENTRY") && params->entry[0] <= 0)
        return (process_int(params, key_str, 'e'));
    else if (strcasestr(key_str, "SEED"))
        return (process_int(params, key_str, 's'));
    else if (strcasestr(key_str, "PERFECT"))
        return (process_str(params, key_str, 'p'));
    else if (strcasestr(key_str, "OUTPUT_FILE")
			 && params->output_file == NULL)
        return (process_str(params, key_str, 'o'));
    return (-1);
}

int process_str(t_param *p, char *key_s, char flag_c)
{
    ssize_t len = 0;
    char    *ret_str = NULL;

    while (*key_s == ' ' || *key_s == '\t')
        key_s++;

    char *eq_sign = strchr(key_s, '=');
    if (!eq_sign)
        return (-1);
    eq_sign++;

    if (flag_c == 'o')
    {
        while (isspace((unsigned char)eq_sign[len]))
            len++;

        if (eq_sign[len] == '\n' || eq_sign[len] == '\0')
            return (-1);

        // skip spases pre-
        eq_sign += len;
        len = 0;

        while (eq_sign[len] != '\n' && eq_sign[len] != '\0')
            len++;

		if (len)
		{
			ret_str = malloc((size_t)len + 1);
			if (!ret_str)
				return (-1);
		}
        	

        memcpy(ret_str, eq_sign, (size_t)len);
        ret_str[len] = '\0';
        p->output_file = ret_str;
        return (len);
    }
    else if (flag_c == 'p')
    {
        while (*eq_sign == ' ' || *eq_sign == '\t')
            eq_sign++;

        while (isalpha((unsigned char)eq_sign[len]))
            len++;

        if (len == 0)
            return (-1);

        /* require exact match for "true" or "false" */
        if ((len == 4 && strncasecmp(eq_sign, "true", 4) == 0) ||
            (len == 5 && strncasecmp(eq_sign, "false", 5) == 0))
        {
            p->perfect = (len == 4 && strncasecmp(eq_sign, "true", 4) == 0);

            char *after_word = eq_sign + len;
            while (*after_word == ' ' || *after_word == '\t' || *after_word == '\n')
                after_word++;

            if (*after_word != '\0')
            {
                printf("ERROR: invalid value for PERFECT: expected true/false\n");
                return (-1);
            }
            return (1);
        }
    }
    return (0);
}

int process_int(t_param *p, char *key_s, char flag_c)
{
    int value[2] = {0, 0};

    while (*key_s == ' ' || *key_s == '\t')
        key_s++;

    char *equal_sign = strchr(key_s, '=');
    if (!equal_sign)
        return (-1);

    if (flag_c == 'e' || flag_c == 'x')
    {
        char *comma = strchr(equal_sign + 1, ',');
        if (!comma)
            return (-1);

        *comma = '\0';

        if (!valid_intstr(equal_sign + 1) || !valid_intstr(comma + 1))
        {
            write(2, "ValueError: invalid literal for atoi(base_10)=", 47);
            write(2, equal_sign + 1, strlen(equal_sign) - 1);
            return (-1);
        }

        value[0] = atoi(equal_sign + 1);
        value[1] = atoi(comma + 1);
        if (flag_c != 's' && (value[0] < 0 || value[1] < 0))
        {
            printf("Can't be negative value.\n");
            return (-1);
        }

        if (flag_c == 'x')
        {
            p->exit[0] = value[0];
            p->exit[1] = value[1];
        }
        else
        {
            p->entry[0] = value[0];
            p->entry[1] = value[1];
        }
    }
    else
    {
        if (!valid_intstr(equal_sign + 1))
        {
            write(2, "ValueError: invalid literal for atoi(base_10)=", 47);
            write(2, equal_sign + 1, strlen(equal_sign) - 1);
            return (-1);
        }
        value[0] = atoi(equal_sign + 1);
        if (flag_c == 'w')
            p->width = value[0];
        else if (flag_c == 'h')
            p->height = value[0];
        else if (flag_c == 's')
            p->seed = value[0];
    }
	return (0);
}
