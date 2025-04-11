#include <stdlib.h>
#include <unistd.h>

int	ft_strlen(char *str)
{
	int	len;

	if (str == NULL)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strchr(char *str, int chr)
{
	while (*str)
	{
		if (*str == (char) chr)
			return (str);
		str++;
	}
	return (NULL);
}

char	*ft_strcpy(char *dest, char *src)
{
	char	*dest_copy;

	dest_copy = dest;
	while (*src)
	{
		*dest_copy = *src;
		dest_copy++;
		src++;
	}
	*dest_copy = '\0';
	return (dest_copy);
}

char	*ft_strdup(char *str)
{
	char	*dup;
	int		i;

	if (str == NULL)
		return (NULL);
	dup = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (dup == NULL)
		return (NULL);
	i = 0;
	ft_strcpy(dup, str);
	return (dup);
}

char	*ft_strjoin(char *str1, char *str2)
{
	int		len1;
	int		len2;
	char	*joined;

	if (!str1 || !str2)
	{
		free(str1);
		return (NULL);
	}
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	joined = malloc(sizeof(char) + (len1 + len2 + 1));
	if (joined == NULL)
	{
		free(str1);
		return (NULL);
	}
	ft_strcpy(joined, str1);
	ft_strcpy(joined + len1, str2);
	free(str1);
	return (joined);
}

char	*ft_read_line(int fd, char *line, char *buf)
{
	int	bytes_read;

	bytes_read = 0;
	while (!ft_strchr(line, '\n'))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buf[bytes_read] = '\0';
		line = ft_strjoin(line, buf);
	}
	if (!line || ft_strlen(line) == 0)
	{
		free(line);
		return (NULL);
	}
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		line[++i] = '\0';
	return (line);
}

char	*ft_update_buffer(char *buf)
{
	char	*new_line;

	new_line = ft_strchr(buf, '\n');
	if (new_line == NULL)
		return (NULL);
	ft_strcpy(buf, new_line + 1);
	return (buf);
}

char	*get_next_line(int fd)
{
	char	*line;
	static char	*buffer[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_strdup(buffer);
	line = ft_read_line(fd, line, buffer);
	if (line == NULL)
		return (NULL);
	ft_update_buffer(buffer);
	return (line);
}
