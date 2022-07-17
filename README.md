# minishell-42
	Tareas:
		mini_split.c (Norme)
		$$ valorar nbr ⎷
		Después de las variables $HOME$ <- Si se introduce un dolar extra imprimirlo ⎷
		Bash si existe un dolar te lo imprime ⎷
		
		Casos expansiones: 
			echo $USER$HOME -> Imprime ambas con ⎷
			echo "$USER$HOME" -> IDEM ⎷
			echo $ ⎷
			echo $USER$ -> aalvarez$ ⎷
			echo $USER$$HOME -> aalvarezHOME ⎷

	Necesidades:
		-Señales ⎷
		-Expansion de binarios ⎷
		-Eliminar el OLDPWD al inicio del programa ⎷
		
		Exec :
			Falta comprobar la ejecución con ruta absoluta ⎷
			Falta comprobar el pwd para ejecutar los ejecutables actuales.⎷
			To upper to lower. ⎷

	Casos de error :
		Trimear comillas para comandos "ls" -l ⎷
		corregir trimeo de casos como echo "'"hola"'" -> 'hola' ⎷
		Echo trim ⎷
		UNSET revision  además de mirar por que no lo pilla en upper
		EXIT si tienes mas de un argumento error ⎷
			-Si tiene un argumento sale ⎷
		EXPANSION DE DOLAR $USE"R" debe dar > R 
		Comprobar que entre pipes haya cosas
		Comprobar que antes de cualquier comando no solo exista una pipe
		Comprobacion cat y wc ⎷
		