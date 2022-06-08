# minishell-42
Tareas :
mini_split.c (Norme)
$$ valorar nbr 
Después de las variables $HOME$ <- Si se introduce un dolar extra imprimirlo
Bash si existe un dolar te lo imprime
Casos expansiones: 
	echo $USER$HOME -> Imprime ambas con ⎷
	echo "$USER$HOME" -> IDEM ⎷
	echo $ ⎷
	echo $USER$ -> aalvarez$ ⎷
	echo $USER$$HOME -> aalvarezHOME 

Necesidades:
	- Funcion comprobación del binario bool isBinary(); Path + directorio actual
	-Comprobar que el último caracter de cualquier string no sea una redirección de cualquier tipo.
	-Expansion de binarios
	-trimmear las comillas dobles y comillas simples en binarios y strings (usar deletecharacter, se eliminan las mismas comillas con las que se abre el string)