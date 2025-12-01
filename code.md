# کد و مثال عملی
در این بخش، مبحث را به شکل عملی و کد بررسی می‌کنیم.
## لیست پیوندی یک‌طرفه
**سوال:**<br>
یک لیست پیوندی یک‌طرفه ایجاد کرده و اعداد 1 تا 1000 را در آن ذخیره کنید.
<br><br>

با تعریف یک node شروع می‌کنیم: (زبان C++)
```C++
class Node{
public:
    int value;
    Node* next = nullptr;
};
```

سر یا head لیست را تعریف می‌کنیم و مقدار 1 را در آن می‌ریزیم:
```C++
Node* head = new Node();
head -> value = 1;
```

با استفاده از یک loop، مقادیر 2 تا 1000 را به لیست اضافه می‌کنیم:
```C++
Node* x = head;
Node* y;

for (int i = 2; i <= 1000; i++){
    y = new Node();
    y -> value = i;
    x -> next = y;
    x = y;
}
```

ساختاری به صورت زیر تولید کردیم:<br>
head -> [1] -> [2] -> ... -> [999] -> [1000] -> nullptr

به این شکل لیست را نمایش می‌دهیم:
```C++
x = head;
for (int i = 1; i <= 1000; i++){
    cout << x -> value << endl;
    x = x -> next;
}
// output: 1 2 3 4 5 ...
```
<br>

### نمایش لیست:
اگر طول لیست پیوندی مشخص نبود، نمایش آن به این شکل انجام می‌شود:
```C++
x = head;
while (x != nullptr){
    cout << x -> value << endl;
    x = x -> next;
}
```

<br>

### درج نود در اول لیست:
```C++
Node* temp = new Node();
temp -> value = 0;
temp -> next = head;
head = temp;
```

### درج نود پس از نود مشخص x:
```C++
Node* temp = new Node();
temp -> value = 0;
temp -> next = x -> next;
x -> next = temp;
```

### درج نود در انتهای لیست:
برای اضافه کردن نود به انتهای لیست، نیاز به آدرس آخرین نود لیست داریم. پیمایش می‌کنیم (در همه حالات فرض می‌کنیم که لیست حداقل 1 عضو دارد):
```C++
Node* last_member = head;
while (last_member -> next != nullptr){
    last_member = last_member -> next;
}
```
حالا نود جدید را به آخر لیست اضافه می‌کنیم:
```C++
Node* temp = new Node();
temp -> value = 0;
last_member -> next = temp;
```


<br>

### حذف نود head:
```C++
head = head -> next;
```
⚠️توجه: در این حالت نود head حذف نشده و منجر به memory leak می‌شود (در ضمیمه توضیح داده شده).

**روش صحیح حذف نود اول:**
```C++
Node* temp = head;
head = head -> next;
delete temp;
```


### حذف نود مشخص x:
در این سوال نیاز به آدرس نود قبل x داریم. پس ابتدا پیمایش انجام می‌دهیم تا نود قبل x را پیدا کنیم:
```C++
Node* before_x = head;
while (before_x -> next != x){
    before_x = before_x -> next;
}
```
حالا نود x را حذف می‌کنیم:
```C++
before_x -> next = x -> next;
delete x;
```

### حذف نود انتهایی:
پیمایش انجام می‌دهیم تا نود یکی به آخر مانده را پیدا کنیم:
```C++
Node* before_last = head;
while (before_last -> next -> next != nullptr){
    before_last = before_last -> next;
}
```
نود آخر را حذف می‌کنیم:
```C++
delete before_last -> next;
before_last -> next = nullptr;
```



## لیست پیوندی حلقوی
کافیست next نود آخر را برابر head قرار دهیم.

نود انتهایی را پیدا می‌کنیم:
```C++
    Node* last_member = head;
    while (last_member -> next != nullptr){
        last_member = last_member -> next;
    }
```
آدرس next نود آخر را برابر با head می‌گذاریم:
```C++
last_member -> next = head;
```

### نمایش لیست:
از head شروع می‌کنیم. زمانی به نود آخر می‌رسیم که next آن برابر با آدرس head باشد:
```C++
x = head;
while (x -> next != head) {
    cout << x -> value << endl;
    x = x -> next;
}
cout << x -> value << endl;
```

### درج نود در انتهای لیست:
همانند لیست پیوندی یک‌طرفه، کافیست در لیست پیمایش کنیم که به عنصر آخر برسیم (شرط next = head در اینجا):
```C++
Node* tail = head;
while (tail -> next != head){
    tail = tail -> next;
}
```
نود جدید را اضافه می‌کنیم:
```C++
Node* temp = new Node();
temp -> value = 1001;
tail -> next = temp;
temp -> next = head;
```

در این حالت، و در حالت اضافه کردن نود در ابتدای لیست، نیاز به پیمایش داریم:
<p align="center"><strong>O(n)</strong></p>

اما می‌توانیم با ذخیره کردن آدرس آخرین عنصر (tail) به جای اولین عنصر، این زمان را به O(1) تبدیل کنیم.
<br>
برای به دست آوردن آدرس head نیز کافیست tail -> next را محاسبه کنیم:
<p align="center"><strong>O(1)</strong></p>

## لیست پیوندی دو طرفه
**سوال:** <br>
 یک لیست پیوندی دو طرفه برای اعداد 1 تا 1000 بسازید.
<br><br>

ابتدا Node را تعریف می‌کنیم:
```C++
class Node{
public:
    int value;
    Node* next = nullptr;
    Node* prev = nullptr;

    Node(int value): value(value) {}
};
```
**نکته:** خط آخر value نود را هنگام ساخت نود مقدار‌ دهی می‌کند.

لیست را می‌سازیم:
```C++
Node* head = new Node(1);

Node* x = head;
Node* y;
for (int i = 2; i <= 1000; i++){
    y = new Node(i);
    y -> prev = x;
    x -> next = y;
    x = y;
}

// ابتدا و انتهای لیست را به هم وصل می‌کنیم:
x -> next = head;
head -> prev = x;
```
**نکته:** در اینجا ابتدا و انتهای لیست را به هم متصل کردیم و یک لیست پیوندی دو طرفه حلقوی ساختیم!

### نمایش لیست:
```C++
x = head;
while (x->next != head){
    cout << x -> value << endl;
    x = x -> next;
}
cout << x -> value << endl;
```

### اضافه کردن نود جدید بعد نود x:
```C++
Node* temp = new Node(0);
temp -> prev = x;
temp -> next = x -> next;
x -> next -> prev = temp;
x -> next = temp;
```

### حذف نود مشخص x:
```C++
x -> next -> prev = x -> prev;
x -> prev -> next = x -> next;
delete x;
```

<br><br>

## ضمیمه 1 - مدیریت حافظه

<details>
<summary>نمایش</summary>

### Memory management:
در زبان های C و C++، وقتی یک متغیر را بدون کلید واژه new تعریف می‌کنیم، برنامه آن را به شکل خودکار، به عنوان یک متغیر محلی (local variable) در stack ذخیره می‌کند. این متغیر‌ها با تمام شدن code block (یعنی کد های داخل {}) نابود می‌شوند.

اما وقتی از کلید واژه new استفاده می‌کنیم در heap ذخیره می‌شوند و از مدیریت خودکار برنامه خارج می‌شوند و تا زمانی که به صورت دستی حذف نشوند حافظه می‌گیرند.

وقتی این خط کد اجرا می‌شود:
```C++
Node* head = new Node();
```
در واقع یک object نود می‌سازیم که در heap ذخیره می‌شود و باید آن را زمانی که به آن دیگر نیاز نداریم به صورت دستی از حافظه پاک کنیم.


پس head آدرس نود را ذخیره می‌کند.
<br>
برای حذف آن از کلید واژه delete استفاده می‌کنیم که اشاره‌گر رو دریافت می‌کند (که در heap باشد) و آن را از حافظه آزاد می‌کند:
```C++
delete head;
```

### قانون طلایی:
<p align="center"><strong>
هر جایی که از new استفاده کردیم باید بعدا آن را با delete آزاد کنیم.
</strong></p>
<br>

### Memory leak:
اگر با new داده تعریف کنیم اما حافظه را بعدا آزاد نکنیم **memory leak** اتفاق می‌افتد.

مثلا در مثال خودمان:

 حذف نود head:
```C++
head = head -> next;
```
نود head هیچ وقت از حافظه پاک نشده، و memory leak اتفاق می‌افتد. فقط از لیست پیوندی خارج شده!

 روش صحیح حذف:

```C++
Node* temp = head;
head = head -> next;
delete temp;
```

<br>

</details>

## ضمیمه 2 - کد های کامل

<details>
<summary>نمایش</summary>

### لیست پیوندی با Loop در C++

<details>
<summary>نمایش کد</summary><br>

شامل:
- insert_head (درج در ابتدای لیست)
- insert_tail (درج در انتهای لیست)
- delete_head (حذف ابتدای لیست)
- delete_tail (حذف انتهای لیست)
- get_length (اندازه لیست)
- print (نمایش کل لیست)

<br>

```C++
#include <iostream>
using namespace std;


class Node{
public:
    int value;
    Node* next = nullptr;
    
    Node(int value): value(value) {}
};


class LinkedList{
public:
    Node* head = nullptr;

    void insert_head(int value){
        Node* temp = new Node(value);
        temp -> next = head;
        head = temp;
    }

    void insert_tail(int value){
        if (head == nullptr){head = new Node(value); return;}
        Node* x = head;
        while (x -> next != nullptr){x = x -> next;}
        x -> next = new Node(value);
    }

    void delete_head(){
        if (head != nullptr){
            Node* temp = head;
            head = head -> next;
            delete temp;
        }
    }

    void delete_tail(){
        if (head == nullptr){return;}
        if(head -> next == nullptr){
            delete head;
            head = nullptr;
            return;
        }
        Node* x = head;
        while (x -> next -> next != nullptr){x = x -> next;}
        delete x -> next;
        x -> next = nullptr;
    }

    int get_length(){
        int length = 0;
        Node* x = head;
        while (x != nullptr){
            x = x -> next;
            length++;
        }
        return length;
    }

    void print(){
        if (head == nullptr){return;}
        Node* x = head;
        while (x -> next != nullptr){
            cout << x -> value << " -> ";
            x = x -> next;
        }
        cout << x -> value << endl;
    }
};


int main(){
    LinkedList linked_list = LinkedList();
    
    linked_list.insert_head(5);
    linked_list.insert_head(3);
    linked_list.insert_head(1);
    linked_list.insert_tail(7);
    linked_list.insert_tail(9);
    
    linked_list.delete_head();
    linked_list.delete_tail();

    cout << linked_list.get_length() << endl;

    linked_list.print();

    return 0;
}
```

</details>

### لیست پیوندی با Recursion در C++

<details>
<summary>نمایش کد</summary><br>

**نکته:** استفاده از loop نسبت به recursion به دلیل استفاده کمتر از حافظه و بهینه تر بودن، ترجیح داد می‌شود.

<br>
شامل:

- insert_tail (درج در انتهای لیست)
- delete_tail (حذف انتهای لیست)
- delete_index (حذف با ایندکس از لیست)
- print (نمایش کل لیست)

<br>

```C++
#include <iostream>
using namespace std;


class Node{
public:
    int value;
    Node* next = nullptr;
    
    Node(int val){
        value = val;
    }

    void insert_tail(int val){
        if (next == nullptr) {
            next = new Node(val);
        }
        else {
            next -> insert_tail(val);
        }
    }

    void print(){
        cout << value;
        if (next != nullptr){
            cout << " -> ";
            next -> print();
        }
    }

    void delete_tail(){
        if (next -> next == nullptr){
            delete next;
            next = nullptr;
        }
        else {
            next -> delete_tail();
        }
    }

    void delete_index(int target, int this_index){
        if (next == nullptr){
            throw runtime_error("Index error!");
        }

        if (target == this_index + 1){
            Node* temp = next -> next;
            delete next;
            next = temp;
        }
        else {
            next -> delete_index(target, this_index + 1);
        }
    }
};


class LinkedList{
public:
    Node* head = nullptr;

    void insert_tail(int value){
        if (head == nullptr){
            head = new Node(value);
        }
        else {
            head -> insert_tail(value);
        }
    }

    void print(){
        if (head != nullptr){
            head -> print();
        }
    }

    void delete_tail(){
        if (head != nullptr){
            if (head -> next == nullptr){
                delete head;
                head = nullptr;
            }
            else {
                head -> delete_tail();
            }
        }
        else {
            throw runtime_error("List is already empty!");
        }
    }

    void delete_index(int index){
        if (index < 0 || head == nullptr){
            throw runtime_error("Index error!");
        }

        if (index == 0){
            Node* temp = head -> next;
            delete head;
            head = temp;
        }
        else {
            head -> delete_index(index, 0);
        }
    }
};


int main(){
    LinkedList mylist;
    mylist.insert_tail(1);
    mylist.insert_tail(3);
    mylist.insert_tail(5);
    mylist.delete_tail();
    mylist.insert_tail(7);
    mylist.delete_index(1);

    mylist.print();

    return 0;
}
```

</details>

### لیست پیوندی با Loop در Python

<details>
<summary>نمایش کد</summary><br>

شامل:

- درج در ابتدا (insert_head) <br>
- درج در انتها (insert_tail) <br>
- حذف از ابتدا (delete_head) <br>
- حذف از انتها (delete_tail) <br>
- نمایش لیست (\_\_str\_\_) <br>
- اندازه لیست (\_\_len\_\_) <br>
- برش لیست (\_\_getitem\_\_) <br>
- جمع دو لیست (\_\_add\_\_) <br>


```Python
class Node:
    def __init__(self, value:int):
        self.value = value
        self.next = None


class LinkedList:
    def __init__(self, values = None):
        self.head = None
        if values:
            for i in values[::-1]:
                self.insert_head(i)


    def insert_head(self, value:int):
        temp = Node(value)
        temp.next = self.head # type: ignore
        self.head = temp


    def insert_tail(self, value:int):
        if self.head == None:
            self.head = Node(value)
        else:
            x = self.head
            while x.next != None:
                x = x.next
            x.next = Node(value) # type: ignore


    def insert_index(self, value:int, index:int):
        if index == 0:
            self.insert_head(value)
            return
        
        this_index = 0
        x = self.head
        while x != None:
            if this_index == index - 1:
                temp = Node(value)
                temp.next = x.next
                x.next = temp # type: ignore
                return
            this_index += 1
            x = x.next

        else:
            raise IndexError("Index out of range!")


    def delete_head(self):
        if self.head:
            self.head = self.head.next
        else:
            raise IndexError("List is already empty!")


    def delete_tail(self):
        if not self.head: raise IndexError("List is already empty!")
        if not self.head.next: self.head = None; return

        x = self.head
        while x.next.next: # type: ignore
            x = x.next # type: ignore

        x.next = None # type: ignore


    def delete_index(self, index):
        if index == 0:
            self.delete_head()
            return
        
        this_index = 0
        x = self.head
        while x != None:
            if this_index == index - 1:
                if not x.next: raise IndexError("Index out of range!")
                x.next = x.next.next
                return
            this_index += 1
            x = x.next

        else:
            raise IndexError("Index out of range!")


    def __getitem__(self, this_slice):
        if isinstance(this_slice, tuple):
            raise KeyError("Maximum one slice is supported!")
        
        nums = []
        x = self.head
        while x != None:
            nums.append(x.value)
            x = x.next

        if isinstance(this_slice, int):
            return nums[this_slice]
        else:
            return LinkedList(nums[this_slice])
        

    def __add__(self, other:"LinkedList") -> "LinkedList":
        if isinstance(other, int):
            new = self.__copy__()
            new.insert_tail(other)
            return new

        elif isinstance(other, LinkedList):
            x = self.head
            if not x: return other
            else:
                new1 = self.__copy__()
                new2 = other.__copy__()
                x = new1.head
                while x.next: #type: ignore
                    x = x.next #type: ignore
                x.next = new2.head #type: ignore
                return new1

        else:
            raise TypeError(f"Operator + not supported for types LinkedList and {type(other)}")

    
    def __len__(self):
        length = 0
        x = self.head
        while x:
            length += 1
            x = x.next

        return length
    

    def __copy__(self) -> "LinkedList":
        nums = []
        x = self.head
        while x != None:
            nums.append(x.value)
            x = x.next

        return LinkedList(nums)


    def __str__(self) -> str:
        ans = ""
        x = self.head
        while x != None:
            ans += str(x.value)
            if x.next != None:ans += " -> "
            x = x.next

        return ans



# مثال های استفاده
linked_list = LinkedList([10, 11, 12])
linked_list.insert_head(5)
linked_list.insert_head(3)
linked_list.insert_tail(7)
linked_list.insert_tail(9)

linked_list.delete_head()
linked_list.delete_tail()

linked_list.insert_index(1, 0)
linked_list.delete_index(1)

print(len(linked_list))
print(linked_list)
print(linked_list[1:3])
linked_list += linked_list[1:3]
print(linked_list)
print(LinkedList([1, 2, 3]) + LinkedList([4, 5, 6]))
```

</details>
