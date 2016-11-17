## Práctica 2

Lo mismo que la práctica 1 pero usando FLEX

para lanzarlo puede hacerse

```bash
python gen_lex.py
```

## Práctica 1

Construir un analizador léxico que devuelva los componentes léxicos que aparecen en el programa regression.d, codificado en el lenguajeD.

 
### Orientación

Los siguientes comentarios tan sólo pretenden servir como sugerencia para el diseño y desarrollo del analizador que se pide. Plantean una forma de resolución un tanto pedestre, pero suficiente, aunque admiten un amplio margen de mejora que será valorado.

Podemos descomponer el diseño en un conjunto de cinco ficheros de código:

1. Un fichero de definiciones accesibles desde los otros tres ficheros
2. Un fichero que albergará el analizador léxico propiamente dicho
3. Un fichero donde implementaremos la tabla de símbolos y sus funciones de acceso
4. Un fichero que albergará el sistema de entrada\
5. Un fichero que albergará el código de gestión de errores. 
6. Adicionalmente, podemos utilizar un fichero que invocará al analizador léxico para solicitar el siguiente componente léxico del código fuente, mostrándolo por pantalla para poder realizar la evaluación de la práctica.

Comentaremos brevemente una posible implementación para estos ficheros:

### FICHERO DE DEFINICIONES

Puede contener las definiciones de los componentes léxicos del lenguaje D utilizados en regresssion.d. Es suficiente con identificar cada componente léxico con un número entero, que el analizador léxico devolverá cada vez que sea invocado. Además, podemos definir aquí la tabla de símbolos como un vector de estructuras que permite almacenar cada uno de los componentes léxicos, y el lexema correspondiente en aquellos casos en los que sea necesario.

Un ejemplo de definición de componentes léxicos de D, en C, podría ser la siguiente:

```C
#define IMPORT 273
#define WHILE 274
...
```

### FICHERO CON EL ANALIZADOR LÉXICO

Puede contener la función más relevante de esta práctica, cuya ejecución supone devolver el siguiente componente léxico del código fuente cada vez que es invocada. Esta función a su vez puede invocar al sistema de entrada para obtener el siguiente carácter del código fuente. Cada vez que obtiene un carácter ejecuta una estructura de autómatas que le permite identificar a qué patrón responde el flujo de entrada, y así devolver su componente léxico correspondiente. Por ejemplo, una vez que encuentra un paréntesis después de leer los caracteres ‘w’,’h’,’i’,’l’,’e’,’c’,’t’,’r’, el analizador debe comprobar que el lexema ‘whilectr' no es una palabra reservada de D, y después ha de incorporarlo a la tabla de símbolos como un identificador. Para terminar, ha de devolver el componente léxico IDENTIFICADOR, y guardar de alguna forma la cadena ‘whilectr'.

Una posible estructura muy sencilla para realizar el analizador podría ser la siguiente:

```C
int seguinte_comp_lexico()
{
     while(!erro){
          switch (estado){
          case 0:
                c = seguinte_caracter(); 
                if (c == ' ' || c == '\t');         
                else if (isapha(c) || c == '_')
                     ...    
                else if (isdigit(c)) {        
                     …
          case 1:
          …
     }
}
```
 
donde la estructura switch implementa un autómata en el que las variables ‘estado’ y ‘c’ permiten simular la ejecución de los distintos AFD que identifican a cada uno de los componentes léxicos del lenguaje. El salto entre los distintos AFD se puede realizar mediante una función fallo() que selecciona el estado del siguiente AFD a simular cuando un AFD no termina su ejecución en un estado de aceptación.

### FICHERO CON LA TABLA DE SÍMBOLOS

Fundamentalmente ha de contener dos funciones imprescindibles: 1) una función de búsqueda que permita recorrer la tabla de símbolos para no replicar innecesariamente el mismo componente léxico; 2) una función de inserción que permita almacenar un nuevo componente léxico encontrado.

### FICHERO CON EL SISTEMA DE ENTRADA

Desde aquí se accede al fichero regression.d para analizarlo como un flujo de caracteres. El sistema de entrada ha de devolver el siguiente carácter del código fuente cada vez que es invocado, y ha de permitir devolver caracteres al flujo de entrada si es necesario. Podemos, por tanto, considerar para ello el diseño de dos funciones.

 

Algunas funciones en C que pueden resultar útiles para el desarrollo de esta práctica:

```C
isalpha(), isdigit(), isalnum(), atoi(), atof(), getc(), strcpy()
```

### TODO:

1. ~~Solucionar problemas con \n y \r~~
2. ~~Soportar comentarios~~
    1. ~~Comentario '//'~~
    2. ~~Comentario '/**/'~~
    3. ~~Comentario '/++/'~~
    4. ~~Comentario '/** */'~~
3. ~~Soportar identificadores bien~~
4. ~~Soportar números bien~~
    1. ~~Hexadecimales~~
    2. ~~Binarios~~
    3. ~~Extensiones...~~
5. ~~Soportar strings~~
6. ~~Sacar caracteres simples~~
7. ~~Entrada por bloques~~
8. ~~Errores~~
9. ~~Operadores multicaracter~~

### BUILD

```bash
    mkdir build
    cd build
    cmake ..
    make
```

### USAGE
```bash
    cd dist/bin
    # ./program <def.h> <source.d>
    ./P1___Comp ../../../src/definitions/definitions.h ../../../regression.d
```