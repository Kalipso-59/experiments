#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node
{
    int data;
    struct node* next;
} Node;


size_t	ft_strlen(const char *str)
{
    size_t	i;

    i = 0;
    while (*str++)
        i++;
    return (i);
} 

void func(char *str) //simple print 
{
    if (!str)
        return ;
    printf("%s\n", str);
}


//function to remove leading 0-es
void removeLeadingZeros(char *str)
{
    if (!str)
        return;
    int len = ft_strlen(str);
    
    int i = 0;
    while (str[i] == '0' && i < len - 1)
    {
        i++;
    }
    //shift rem chars to the beggining
    int j = 0;
    while (i < len)
    {
        str[j] = str[i];
        i++;
        j++;
    }
    str[j] = '\0';
}

int is_number(char *str)  //check for valid numbers
{
    if (!str)
        return 0;
     removeLeadingZeros(str); 
    int i = 0;
    int has_digit = 0;
    int has_minus = 0;
    int has_other = 0;

    while (str[i] != '\0') {
        if (str[i] == '-') {
            if (i == 0 || str[i - 1] == ' ')
            {
                has_minus = 1;
            }
            else
            {
                has_other = 1;
                break;
            }
        } else if (str[i] >= '0' && str[i] <= '9') {
            has_digit = 1;
        } else if (str[i] != ' ') {
            has_other = 1;
            break;
        }
        i++;
    }
    return has_digit && !has_other && (has_minus <= 1);
}

//convert to int, check range... but 0?
int int_range(char *str)
{
    long num = 0;
    int sign = 1;
    int i = 0;
    if (!str)
        return 0;
    if (str[0] == '-')
    {
        sign = -1;
        i++;
    }
    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            num = num * 10 + (str[i] - '0');
            i++;
        } else {
            return 0;
        }
    }
    num *= sign;
    if (num < INT_MIN || num > INT_MAX)
        return 0;
        
    return 1;  //return num and add *error by refernce, to count 0 case
}

//check duplicates in stack;

//to do


char	*ft_strdup(const char *str)
{
    int		str_len;
    char	*dup;
    int		i;

    i = 0;
    str_len = ft_strlen(str);
    dup = (char *)malloc(sizeof(char) * str_len + 1);
    if (dup == NULL)
        return (NULL);
    while (str[i])
    {
        dup[i] = str[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
    char	*substr;
    size_t	s_len;
    size_t	i;

    if (!s)
        return (NULL);
    s_len = ft_strlen(s);
    if (start >= s_len)
        return (ft_strdup(""));
    if (len > s_len - start)
        len = s_len - start;
    substr = (char *)malloc(len + 1);
    if (!substr)
        return (NULL);
    i = 0;
    while (i < len)
    {
        substr[i] = s[start + i];
        i++;
    }
    substr[i] = '\0';
    return (substr);
}

void	free_memory(char **ptr_ss, long index)
{
    while (index)
    {
        free(ptr_ss[index]);
        index--;
    }
    free(ptr_ss);
}

long	count_of_words(char const *s, char c)
{
    long	count;
    long	found_word;

    found_word = 1;
    count = 0;
    while (*s)
    {
        if (*s == c)
            found_word = 1;
        else
        {
            if (found_word)
            {
                count++;
                found_word = 0;
            }
        }
        s++;
    }
    return (count + 1);
}

long	word_len(char const *s, char c, long i)
{
    long	len;

    len = 0;
    while (s[i] && s[i] != c)
    {
        len++;
        i++;
    }
    return (len);
}

char	**ft_split(char const *s, char c)
{
    char	**res;
    long	i;
    long	j;

    if (!s)
        return (NULL);
    res = (char **)malloc((count_of_words(s, c)) * sizeof(char *));
    i = 0;
    j = -1;
    if (!res)
        return (NULL);
    while (++j < count_of_words(s, c) - 1)
    {
        while (s[i] == c)
            i++;
        res[j] = ft_substr(s, i, word_len(s, c, i));
        if (!res[j])
        {
            free_memory(res, j);
            return (NULL);
        }
        i += word_len(s, c, i);
    }
    res[j] = 0;
    return (res);
}


char	*ft_strjoin(char *s1, char *s2)
{
    int		s1_i;
    int		s2_i;
    char	*con;

    s1_i = 0;
    s2_i = 0;
    con = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2)); //' ' '\0'
    if (!con)
        return (NULL);
    while (s1 && s1[s1_i] != '\0')
    {
        con[s1_i] = s1[s1_i];
        s1_i++;
    }
    con[s1_i] = ' ';
    s1_i++;
    while (s2 && s2[s2_i] != '\0')
    {
        con[s1_i] = s2[s2_i];
        s1_i++;
        s2_i++;
    }
    con[s1_i] = '\0';
    //free (s1);  ///??????????????????????? Dies here with sanitise flag, why?
    return (con);
}


//for split to work
int pars(char *res)
{
    //   char *str = "1 2 3 4a   7 8a z";/
    char *str = res;
    char c = ' ';
    char **result = ft_split(str, c);

    if (result == NULL)
    {
        printf("Error: ft_split returned NULL\n");
        return 0;
    }
    for (int i = 0; result[i] != NULL; i++)
    {
        func(result[i]); //print
    }
    free(result);
    return 1;
}

int main(int argc, char **argv)
{
    char *res = NULL;
    if (argc > 1)
    {
        res = argv[1];
        for (int i = 2; i < argc; i++)
        {
            res = ft_strjoin(res, argv[i]);
        }
        //printf("%s", res);
        if (!res)
            return 1;   ///?????Do I really need this?
        else
        {
           if (pars(res) == 0)
           {
               printf("Not valid input");
               exit(1);
           }
           else
           {
               
           }
        }
    }
    else
    {
        printf("Error no input");
    }
}
