# minishell-42
	Tareas:
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
		UNSET revision  además de mirar por que no lo pilla en upper ⎷
		EXIT si tienes mas de un argumento error ⎷
			-Si tiene un argumento sale ⎷
		EXPANSION DE DOLAR $USE"R" debe dar > R 
		Comprobar que entre pipes haya cosas
		Comprobar que antes de cualquier comando no solo exista una pipe
		Comprobacion cat y wc ⎷
		
		Tareas
		SHLEVEL comprobar
		Double pipe  ⎷
		Pipe entre medias
		Doble comando pasar información entre pipes⎷
		
		Overflow on trim minishell
		Split on get_actual_path()
		Exit licazos
		Dolar value linea 57 echo $?
		Preguntar que hace cntrol \
		Control d debería salirse (exit)
		No detectar redirecciones entre comillas
		leak cd -
		cd ~
		Objetos
		



		