# SplayTree v1.0.0 - Release

Este es un proyecto realizado a modo de práctica, donde se crea una librería con la estructura de SplayTree.

Pero, ¿que és un **Splay Tree**?

Un Splay Trees es un **árbol de búsqueda autoajustable que no realiza comprobación de la existencia de datos repetidos**.

Dicha estructura de datos, está compuesta de nodos, los cuáles he decidido definirlos cómo un “Struct” en lugar de una
clase debido a que todos los datos que este tiene han de ser públicos para así poder realizar todas las operaciones deseadas.

Así mismo, la estructura nodo, está compuesta de otros 3 nodos y el valor de dicho nodo. Estos son, el hijo izquierdo, el
hijo derecho y el nodo padre.

La existencia de un puntero al nodo padre es realmente interesante, porque durante el planteamiento inicial no existía, esto
es debido a que de primeras, y siguiendo la estructura de un árbol normal, este no debería saber quién es su padre, no obstante,
para crear un Splay Tree necesitaremos saber en muchas ocasiones quién es el padre o incluso el abuelo del nodo que estamos
tratando, por tanto, resulta impracticable realizar una búsqueda de estos desde la raíz (no sólo en términos de complejidad,
sino también en que un dato puede estar varias veces, y no sabríamos a cuál nos estamos refiriendo).

Una vez aclarado el “Struct” nodo del que se compondrá la estructura, hay que entrar ya de lleno en la clase de esta.

Cómo datos privados de esta clase, he creado un nodo “root” que será considerado el origen, o la raíz de nuestro Splay Tree.
Este nodo siempre tendrá que tener cómo padre “NULL”.

Por otro lado, cómo métodos privados, he creado de manera auxiliar y para ir testeando el código, 3 métodos básicos de recorridos
de un árbol (inorden, preorden y postorden).

También he creado un método “destruir” que simplemente ayuda a borrar todos los nodos y liberar la memoria dinámica si es que la
clase ha sido creada dinámicamente (realmente no lo uso).

Ahora, y entrando en uno de los métodos más importantes, esta “Splay” o flotación, el cuál ha sido creado de manera iterativa en
lugar de recursiva debido a que las propuestas recursivas eran poco “elegantes”, no obstante, considero que puede haber opciones
recursivas, realmente buenas.

Continuando con este método, realizo un bucle que se repetirá hasta que el nodo desde el cuál realizo el “Splay” suba a la raíz,
cuando esto ocurra, al salir del bucle, actualizo el valor de mi variable “root” con dicho nodo.

Dentro del bucle obtengo el padre y el abuelo del nodo, sabiendo que si no tiene padre ha terminado (porque ya es la posición
root, cómo queríamos) y que si no tiene abuelo haremos una última rotación y saldremos.

Por otro lado, si tiene abuelo, deberé realizar dos rotaciones (una sobre padre y otra sobre abuelo), dependiendo de en qué lado
(en comparación con padre y abuelo) se encuentra nuestro nodo y continuará con otra vuelta del bucle (teniendo en cuenta que
nuestro nodo ya ha escalado parcialmente por el Splay Tree).

Por último, los métodos públicos son “insertar”, “buscar”, “borrar”, los 3 métodos de recorridos de listas (llaman a su vez a
los 3 métodos privados anteriormente descritos) y un método extra auxiliar que también sirve para mostrar el árbol, en esta
ocasión de una forma muy clara.

- El método insertar primeramente comprobará si nuestro Splay Tree está vacío, si es así directamente creará el nodo y lo pondrá
en “root”, si no es así, empieza el algoritmo de verdad.
Irá buscando en qué posición le tocará insertarse, para ello mira el nodo y si el valor a insertar es mayor que el nodo, sigue
mirando a la derecha, si es menor, sigue mirando hacia la izquierda.
Si en algún momento hacia el lado que le toca mirar se encuentra a “NULL”, directamente lo inserta ahí y finalmente realizaría
un “Splay” desde ese nodo (para ponerlo en “root”).
Cómo detalle, aclarar, que si el nodo que estamos mirando es igual que el que estamos insertando he elegido arbitrariamente 
insertarlo a la izquierda.

- El método buscar inicialmente devuelve “NULL” si “root” vale “NULL” (es decir si el árbol es vacío), y si no, lo que hará es
mirar hacia la derecha si el valor buscado es mayor que el nodo que estás mirando, y por lo mismo, irá a la izquierda si es menor.
Si encuentra un nodo con el valor buscado, se detiene, realiza el “Splay” sobre ese nodo y lo devuelve.
Si no encuentra el valor (es decir, no ha sido insertado previamente), cuando llegue a una hoja termina la ejecución realizando
un “Splay” de dicha hoja y devolviéndola.

- El método borrar, inicialmente llama al método buscar (con lo que el nodo buscado o bien está en la raíz o bien no está).
Comprueba si el valor buscado (el de la raíz) es que el queríamos, si no es así, termino la ejecución y devuelvo que no lo ha
podido borrar.