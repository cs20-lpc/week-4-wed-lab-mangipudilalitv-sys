template <typename T>
DoublyList<T>::DoublyList()
: header(new Node), trailer(new Node) {
    header->next  = trailer;
    trailer->prev = header;
    this->length = 0;
}

template <typename T>
DoublyList<T>::DoublyList(const DoublyList<T>& copyObj)
: header(new Node), trailer(new Node) {
    header->next  = trailer;
    trailer->prev = header;
    this->length = 0;
    copy(copyObj);
}

template <typename T>
DoublyList<T>& DoublyList<T>::operator=(const DoublyList<T>& rightObj) {
    if (this != &rightObj) {
        clear();
        copy(rightObj);
    }
    return *this;
}

template <typename T>
DoublyList<T>::~DoublyList() {
    clear();
    delete header;
    delete trailer;
    header = trailer = nullptr;
}

template <typename T>
void DoublyList<T>::append(const T& elem) {
    Node* last = trailer->prev;
    Node* n = new Node(elem);

    n->prev = last;
    n->next = trailer;

    last->next = n;
    trailer->prev = n;

    this->length++;
}

template <typename T>
void DoublyList<T>::clear() {
    for (Node* curr = nullptr; header->next != trailer; ) {
        curr = header->next->next;
        delete header->next;
        header->next = curr;
    }

    trailer->prev = header;
    this->length  = 0;
}

template <typename T>
void DoublyList<T>::copy(const DoublyList<T>& copyObj) {
    // assume *this is already an empty valid list (sentinels linked)
    this->length = 0;

    Node* copyCurr = copyObj.header->next;
    while (copyCurr != copyObj.trailer) {
        append(copyCurr->value);
        copyCurr = copyCurr->next;
    }
}

template <typename T>
T DoublyList<T>::getElement(int position) const {
    if (position < 0 || position >= this->length) {
        return T();
    }

    Node* curr = header->next;
    for (int i = 0; i < position; i++) {
        curr = curr->next;
    }
    return curr->value;
}

template <typename T>
int DoublyList<T>::getLength() const {
    return this->length;
}

template <typename T>
void DoublyList<T>::insert(int position, const T& elem) {
    if (position < 0 || position > this->length) return;

    if (position == this->length) {
        append(elem);
        return;
    }

    Node* curr = header->next;
    for (int i = 0; i < position; i++) {
        curr = curr->next;
    }

    Node* before = curr->prev;
    Node* n = new Node(elem);

    n->prev = before;
    n->next = curr;

    before->next = n;
    curr->prev = n;

    this->length++;
}

template <typename T>
bool DoublyList<T>::isEmpty() const {
    return this->length  == 0
        && header->next  == trailer
        && trailer->prev == header;
}

template <typename T>
void DoublyList<T>::remove(int position) {
    if (position < 0 || position >= this->length) return;

    Node* curr = header->next;
    for (int i = 0; i < position; i++) {
        curr = curr->next;
    }

    Node* before = curr->prev;
    Node* after  = curr->next;

    before->next = after;
    after->prev  = before;

    delete curr;
    this->length--;
}

template <typename T>
bool DoublyList<T>::search(const T& elem) const {
    for (Node* curr = header->next; curr != trailer; curr = curr->next) {
        if (curr->value == elem) return true;
    }
    return false;
}

template <typename T>
void DoublyList<T>::replace(int position, const T& elem) {
    if (position < 0 || position >= this->length) return;

    Node* curr = header->next;
    for (int i = 0; i < position; i++) {
        curr = curr->next;
    }

    curr->value = elem;
}

template <typename U>
ostream& operator<<(ostream& outStream, const DoublyList<U>& myObj) {
    if (myObj.isEmpty()) {
        outStream << "List is empty, no elements to display.\n";
    } else {
        typename DoublyList<U>::Node* curr = myObj.header->next;
        while (curr != myObj.trailer) {
            outStream << curr->value;
            if (curr->next != myObj.trailer) {
                outStream << " <-> ";
            }
            curr = curr->next;
        }
        outStream << endl;
    }
    return outStream;
}