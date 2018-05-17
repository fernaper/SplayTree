
/**
 * Practica de MARP primer cuatrimestre Arboles Autoajustables (o SplayTree).
 * @author Joaquin
 */

class SplayTree<Key extends Comparable<Key>>{
    private Node root;

    SplayTree(){
        root = null;
    }

    /**
     * Busca el nodo con la clave value y en caso de encotrarlo lo elimina, sino elimina el nodo que resulte de la busqueda.
     * @param value Clave que se desea borrar del arbol.
     */
    boolean remove(Key value){
        if(root == null){
            return false;
        }
        Node aux;
        aux = search(value);//Primero busco el nodo lo cual implica un splay y colocarlo en la raiz

        Node right = null, left = null;
        if(aux.right != null){//Corto al nodo/arbol derecho de su padre, en caso de no ser nulo.
            right = new Node(root.right);
            aux.right = null;
        }
        if(aux.left != null){//Corto al nodo/arbol izquierdo de su padre, en caso de no ser nulo.
            left = new Node(root.left);
            aux.left = null;
        }
        //Una vez cortados los arboles del padre que hemos deshechado nos quedan dos arboles, en caso de no tener abol izquierdo, el derecho se establece como raiz.
        if(left != null){
            Node aux2 = null;
            int cmp;
            if(left.right != null){//Si el arbol izquierdo no es nulo busco el nodo mas grande que establecere como raiz quedando asi la raiz solo con hijo izquierdo y enlazo el arbol derecho alli
                cmp = left.value.compareTo(left.right.value);
                aux2 = left.right;
                while(cmp < 0){
                    if(aux2.right == null){
                        cmp = 5;//Fuerzo la salida del bucle pues he encontrado la posicion correcta.
                    }
                    else {//Comparo y sigo actualizando
                        cmp = aux2.value.compareTo(aux2.right.value);
                        aux2 = aux2.right;
                    }
                }
                left = splay(aux2);//Una vez encontrado el nodo, realizo splay le corto el padre, lo dejo como raiz del arbol y en el hijo izquierdo le dejo el otro arbol.
                left.setParent(null);
                left.right = right;
                root = left;
            }
        }
        else{
            root = right;
        }

        return true;
    }

    /**
     * Search for the node with key value.
     * Busca el nodo con la clave value, y luego realiza splay.
     * @param value Clave que se busca en el arbol.
     * @return Nodo con clave value.
     */
    Node search(Key value){
        if(root == null){//En caso de ser un arbol vacio paro y retorno nulo.
            return null;
        }
        Node aux = root;
        while(aux != null){//Mientras la busqueda no me haya llevado a un nodo nulo, continuo en el bucle.
            if(value == aux.value){// Si he encontrado el nodo buscado salgo del bucle.
                break;
            }
            if(value.compareTo(aux.value) < 0){//Mientras no lo haya encontrado comparo valores en caso de ser menor que 0 continuo por el hijo izquierdo del arbol.
                if(aux.left == null) {
                    break;
                }
                aux = aux.left;

            }
            else{//Mientras no lo haya encontrado comparo valores en caso de ser mayor o igual que 0 continuo por el hijo derecho del arbol.
                if(aux.right == null){
                    break;
                }
                aux = aux.right;
            }
        }
        aux = splay(aux);//Al encontrar el nodo deseado se realiza un splay
        this.root = aux;
        return aux;
    }


    /**
     * Inserts a node in the the SplayTree.
     * Realiza la insercion de un nuevo nodo en el arbol.
     * @param value Valor del nodo que queremos insertar en el arbol.
     */
    void insert(Key value){
        if(root == null){
            root = new Node(value);
            return;
        }
        int cmp;
        boolean added = false;
        Node aux = root;
        while(!added) {//Si el nodo no esta añadido comparamos claves asta colocarlo en su posicion correspondiente, una vez colocado realizamos un splay.
            cmp = value.compareTo(aux.value);
            if (cmp < 0 ) {//Si es menor continuo por el lado izquierdo
                if(aux.left != null){//Mientras por el lado izquierdo no pueda poner un hijo continuo bajando en el arbol.
                    aux = aux.left;
                }
                else {//Al estar en una posicion donde pudeo insertar genero el nodo, lo inserto, realizo un splay, y cambio el flagg a added para salir del bucle.
                    aux.left = new Node(value);
                    aux.left.setParent(aux);
                    aux = splay(aux.left);
                    added = true;
                }
            }
            else{//En caso de ser mayor o igual coninuaria por el lado derecho.
                if(aux.right != null) {//Mientras por el lado derecho no pueda insertar un hijo continuo bajando por el arbol,
                    aux = aux.right;
                }
                else{//Al estar en una posicion donde pudeo insertar genero el nodo, lo inserto, realizo un splay, y cambio el flagg a added para salir del bucle.
                    aux.right = new Node(value);
                    aux.right.setParent(aux);
                    aux = splay(aux.right);
                    added = true;
                }
            }
        }
        this.root = aux;
    }

    /**
     * Funcion splay del arbol, dado un nodo realiza splay sobre el mismo.
     * @param root
     * @return
     */
    private  Node splay(Node root){
        Node parent ;
        while(true){
            parent = root.getParent();

            if(parent == null || parent.value == null){//Si no tiene padre paramos de realizar splay pues hemos llegado a la raiz
                break;
            }
            Node grandParent = parent.getParent();
            if(grandParent == null ){// Mientras tenga abuelo compruebo y realizo las rotaciones pertinentes
                if(parent.left == root){//Cuando root es hijo directo de la raiz del arbol y es el hijo izquierdo de la misma.
                    root = rotateRight(parent);
                }
                else{
                    root = rotateLeft(parent);//Cuando root es hijo directo de la raizdel arbol y es el hijo derecho de la misma.
                }
                break;// Una vez se a realizado la rotacion con el padre pasa a ser el nodo root la raiz del arbol asique salimos del bucle
            }

            if(grandParent.left == parent){// En caso de que nuestro abuelo sea por el lado izquierdo de nuestro padre hay os siguientes dobles desequilibrio posibles:
                if(parent.left == root){
                    root = rotateLL(grandParent);//Desequilibrio izquierda-izquierda (que correspondera a dos rotaciones hacia la derecha)
                }
                else{
                    root = rotateRL(grandParent);//Desequilibrio derecha-izquierda (que corresponde una rotacion derecha y otra a la izquierda)

                }

            }
            else{// En caso de que nuestro abuelo sea por el lado derecho de nuestro padre hay os siguientes dobles desequilibrio posibles:
                if(parent.left == root){
                    root = rotateLR(grandParent); //Desequilibrio izquierda-derecha (que corresponde una rotacion derecha y otra a la izq).

                }
                else{
                    root = rotateRR(grandParent); //Desequilibrio derecha-derecha (que correspondera a dos rotaciones hacia la izquierda)
                }
            }
        }
        return root;
    }

    private Node rotateRight(Node root){
        Node p = new Node(root.value), q = new Node(root.left.value);//Corto los nodos p y q del arbol, los dejo solo con su valor
        Node a = new Node(root.left.left), b = new Node(root.left.right), c = new Node(root.right);// corto de sus padres los nodos/arboles a,b,c

        //Procedo a reestructurar un arbol resultante de la rotacion solo con p y q.
        q.right = p;
        p.setParent(q);
        q.setParent(root.getParent());
        //Los hijos a,b y c pueden ser nodos o arboles que tienen que seguir enlazados.
        if(a.value != null){// En caso de que 'a' sea un nodo/arbol lo engancho sino no hago nada dejando a null esta zona para su posible padre
            q.left = a;
            a.setParent(q);
        }
        if(b.value != null){// En caso de que 'b' sea un nodo/arbol lo engancho sino no hago nada dejando a null esta zona para su posible padre
            p.left = b;
            b.setParent(p);
        }
        if(c.value != null){// En caso de que 'c' sea un nodo/arbol lo engancho sino no hago nada dejando a null esta zona para su posible padre
            c.setParent(p);
            p.right = c;
        }
        //Compruebo cual era el padre anterior del arbol que estoy reestructurando y engancho en ese lugar el arbol que resultante, se quedara nulo en caso de haber llegado a la cima.
        if(q.getParent() != null && q.getParent().right == root){
            q.getParent().right = q;
        }
        else if(q.getParent() != null && q.getParent().left == root){
            q.getParent().left = q;
        }
        return q;
    }

    private Node rotateLeft(Node root){
        Node p = new Node(root.value), q = new Node(root.right.value);//Corto los nodos p y q del arbol, los dejo solo con su valor
        Node a = new Node(root.left), b = new Node(root.right.left), c = new Node(root.right.right);// corto de sus padres los nodos/arboles a,b,c
        //Procedo a reestructurar un arbol resultante de la rotacion solo con p y q.
        q.left = p;
        p.setParent(q);
        q.setParent(root.getParent());
        //Los hijos a,b y c pueden ser nodos o arboles que tienen que seguir enlazados.
        if(a.value != null){// En caso de que 'a' sea un nodo/arbol lo engancho sino no hago nada dejando a null esta zona para su posible padre
            a.setParent(p);
            p.left = a;
        }
        if(b.value != null){// En caso de que 'b' sea un nodo/arbol lo engancho sino no hago nada dejando a null esta zona para su posible padre
            p.right = b;
            b.setParent(p);
        }
        if(c.value != null){// En caso de que 'c' sea un nodo/arbol lo engancho sino no hago nada dejando a null esta zona para su posible padre
            c.setParent(q);
            q.right = c;
        }
        //Compruebo cual era el padre anterior del arbol que estoy reestructurando y engancho en ese lugar el arbol que resultante, se quedara nulo en caso de haber llegado a la cima.
        if(q.getParent() != null && q.getParent().right == root){
            q.getParent().right = q;
        }
        else if(q.getParent() != null && q.getParent().left == root){
            q.getParent().left = q;
        }
        return q;
    }

    private Node rotateLL(Node root) {
        Node gp = new Node(root.value),p = new Node(root.left.value),q = new Node(root.left.left.value);//Corto los nodos gp,p y q del arbol, los dejo solo con su valor.
        Node a = new Node(root.left.left.left), b =  new Node(root.left.left.right), c = new Node(root.left.right), d = new Node(root.right) ;// Corto de sus padres los nodos/arboles a,b,c,d
        //Procedo a reestructurar un arbol resultante de la rotacion solo con gp,p y q.
        q.right = p;
        p.right = gp;
        p.setParent(q);
        gp.setParent(p);
        q.setParent(root.getParent());
        //Los hijos a,b,c y d pueden ser nodos o arboles que tienen que seguir enlazados.
        if(a.value != null){// En caso de que 'a' sea un nodo/arbol lo engancho sino no hago nada dejando a null esta zona para su posible padre
            q.left = a;
            a.setParent(q);
        }
        if(d.value != null){// En caso de que 'd' sea un nodo/arbol lo engancho sino no hago nada dejando a null esta zona para su posible padre
            d.setParent(gp);
            gp.right = d;
        }
        if(b.value != null){// En caso de que 'b' sea un nodo/arbol lo engancho sino no hago nada dejando a null esta zona para su posible padre
            p.left = b;
            b.setParent(p);
        }
        if(c.value != null){// En caso de que 'c' sea un nodo/arbol lo engancho sino no hago nada dejando a null esta zona para su posible padre
            c.setParent(gp);
            gp.left = c;
        }
        //Compruebo cual era el padre anterior del arbol que estoy reestructurando y engancho en ese lugar el arbol que resultante, se quedara nulo en caso de haber llegado a la cima.
        if(q.getParent()  != null && q.getParent().right == root){
            q.getParent().right = q;
        }
        else if(q.getParent()  != null && q.getParent().left == root){
            q.getParent().left = q;
        }
        return q;
    }

    private Node rotateLR(Node root) {
        Node a = new Node(root.left), b = new Node(root.right.left.left), c = new Node(root.right.left.right), d = new Node(root.right.right);//Corto los nodos gp,p y q del arbol, los dejo solo con su valor.
        Node gp = new Node(root.value), p = new Node(root.right.value), q = new Node(root.right.left.value);// Corto de sus padres los nodos/arboles a,b,c,d
        //Procedo a reestructurar un arbol resultante de la rotacion solo con gp,p y q.
        q.left = gp;
        q.right = p;
        gp.setParent(q);
        p.setParent(q);
        q.setParent(root.getParent());
        //Los hijos a,b,c y d pueden ser nodos o arboles que tienen que seguir enlazados.
        if (c.value != null){// En caso de que 'c' sea un nodo/arbol lo engancho sino no hago nada dejando a null esta zona para su posible padre
            p.left = c;
            c.setParent(p);
        }
        if(d.value != null) {// En caso de que 'd' sea un nodo/arbol lo engancho sino no hago nada dejando a null esta zona para su posible padre
            p.right = d;
            d.setParent(p);
        }
        if(a.value != null) {// En caso de que 'a' sea un nodo/arbol lo engancho sino no hago nada dejando a null esta zona para su posible padre
            gp.left = a;
            a.setParent(gp);
        }
        if(b.value != null) {// En caso de que 'b' sea un nodo/arbol lo engancho sino no hago nada dejando a null esta zona para su posible padre
            b.setParent(gp);
            gp.right = b;
        }
        //Compruebo cual era el padre anterior del arbol que estoy reestructurando y engancho en ese lugar el arbol que resultante, se quedara nulo en caso de haber llegado a la cima.
        if(q.getParent()  != null && q.getParent().right == root){
            q.getParent().right = q;
        }
        else if(q.getParent()  != null && q.getParent().left == root) {
            q.getParent().left = q;
        }
        return q;
    }

    private  Node rotateRR(Node root){
        Node gp = new Node(root.value),p = new Node(root.right.value),q = new Node(root.right.right.value);//Corto los nodos gp,p y q del arbol, los dejo solo con su valor.
        Node a = new Node(root.left), b =  new Node(root.right.left), c = new Node(root.right.right.left), d = new Node(root.right.right.right) ;// Corto de sus padres los nodos/arboles a,b,c,d
        //Procedo a reestructurar un arbol resultante de la rotacion solo con gp,p y q.
        q.left = p;
        p.left = gp;
        p.setParent(q);
        gp.setParent(p);
        q.setParent(root.getParent());

        if(a.value != null){// En caso de que 'a' sea un nodo/arbol lo engancho sino no hago nada dejando a null esta zona para su posible padre
           gp.left = a;
           a.setParent(gp);
        }
        if(d.value != null){// En caso de que 'd' sea un nodo/arbol lo engancho sino no hago nada dejando a null esta zona para su posible padre
            d.setParent(q);
            q.right = d;
        }
        if(b.value != null){// En caso de que 'b' sea un nodo/arbol lo engancho sino no hago nada dejando a null esta zona para su posible padre
            b.setParent(gp);
            gp.right = b;
        }
        if(c.value != null){// En caso de que 'c' sea un nodo/arbol lo engancho sino no hago nada dejando a null esta zona para su posible padre
            p.right = c;
            c.setParent(p);
        }
        //Compruebo cual era el padre anterior del arbol que estoy reestructurando y engancho en ese lugar el arbol que resultante, se quedara nulo en caso de haber llegado a la cima.
        if(q.getParent()  != null && q.getParent().right == root){
            q.getParent().right = q;
        }
        else if(q.getParent()  != null && q.getParent().left == root) {
            q.getParent().left = q;
        }
        return q;
    }

    private Node rotateRL(Node root){
        Node gp = new Node(root.value),p = new Node(root.left.value),q = new Node(root.left.right.value);//Corto los nodos gp,p y q del arbol, los dejo solo con su valor.
        Node a = new Node(root.left.left), b = new Node(root.left.right.left), c = new Node(root.left.right.right), d = new Node(root.right) ;// Corto de sus padres los nodos/arboles a,b,c,d
        //Procedo a reestructurar un arbol resultante de la rotacion solo con gp,p y q.
        q.left = p;
        q.right = gp;
        q.setParent(root.getParent());
        p.setParent(q);
        gp.setParent(q);
        //Los hijos a,b,c y d pueden ser nodos o arboles que tienen que seguir enlazados.
        if(a.value != null){// En caso de que 'a' sea un nodo/arbol lo engancho sino no hago nada dejando a null esta zona para su posible padre
            p.left = a;
            a.setParent(p);
        }
        if(b.value != null){// En caso de que 'b' sea un nodo/arbol lo engancho sino no hago nada dejando a null esta zona para su posible padre
            p.right = b;
            b.setParent(p);
        }
        if(c.value != null){// En caso de que 'c' sea un nodo/arbol lo engancho sino no hago nada dejando a null esta zona para su posible padre
            gp.left = c;
            c.setParent(gp);
        }
        if(d.value != null){// En caso de que 'd' sea un nodo/arbol lo engancho sino no hago nada dejando a null esta zona para su posible padre
            d.setParent(gp);
            gp.right = d;
        }
        //Compruebo cual era el padre anterior del arbol que estoy reestructurando y engancho en ese lugar el arbol que resultante, se quedara nulo en caso de haber llegado a la cima.
        if(q.getParent()  != null && q.getParent().right == root){
            q.getParent().right = q;
        }
        else if(q.getParent()  != null && q.getParent().left == root) {
            q.getParent().left = q;
        }
        return q;
    }

    /**
     * Clase nodo con constructor para cortar del arbol o generar nodos nulos, y constructor para generar nodos individuales.
     */
    private class Node{
        private Node parent;
        Node left;
        Node right;
        Key value;

        Node(Key value){
            this.value = value;
            this.left = null;
            this.right = null;
            this.parent = null;
        }
        Node(Node node){
            if(node != null){
                this.value = node.value;
                this.left = node.left;
                this.right = node.right;
                this.parent = null;
                if(this.right != null)
                    this.right.setParent(this);
                if(this.left != null)
                    this.left.setParent(this);
            }
            else{
             this.value = null;
             this.right = null;
             this.left = null;
             this.parent = null;
            }
        }
        Node getParent(){
            return this.parent;
        }
        void setParent(Node node){
            this.parent = node;
        }
    }
}
