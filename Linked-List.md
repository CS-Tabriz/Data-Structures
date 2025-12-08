# درسنامه لیست‌های پیوندی (Linked Lists)
##  لیست پیوندی چیست؟

لیست پیوندی یک <b>ساختار داده‌ای خطی</b> است که از مجموعه‌ای از <b>"گره"ها (Node)</b> ساخته شده‌است.
هر "گره" شامل دو بخش است:


در لیست پیوندی شما می‌توانید هر آیتم را در هر کجای حافظه قرار دهید، اما باید جایگاه آیتم بعدی را هم در کنار آن آیتم قرار بدهید، در واقع لیست پیوندی مجموعه‌ای از داده‌ها است که به صورت پراکنده در حافظه ذخیره‌ شده‌اند و هر کدام با داشتن آدرس گره بعدی در حافظه به آن متصل شده‌است.
<br>
<br>

هر "node" یا "گره" در یک لیست پیوندی به دو قسمت نیاز دارد:
<br>

- <b>دیتا (Data)</b>: داده‌ای که "گره" نگه می‌دارد
- <b>اشاره‌گر (Pointer/Next)</b>: آدرس "گره" بعدی

```
      +-----------+-----------+
      |   DATA    |   POINTER |
      |  (مقدار)    | (آدرس بعدی) |
      +-----------+-----------+
            \           /
             \_________/
                  |
              یک گره (Node)
```
 در واقع به جای اینکه مثل آرایه، همه‌ی عناصر کنار هم در حافظه باشند، هر گره با داشتن آدرس گره بعدی به آن متصل می‌شود.

##  ساختار یک "گره" و لیست پیوندی

### ساختار node یا گره
```text
Data | Next
```
برای ساخت یک گره حداقل نیاز به یک داده برای ذخیره و یک pointer برای اشاره به گره بعدی داریم.
### مثال

```
Memory Addresses:            1001         1020          1190
Nodes:                     [10|1020] -> [20|1190] -> [30|Next] -> None
```

-  شروع لیست از <b>"Head"</b> است که به اولین گره لیست اشاره می‌کند.
-   به آخرین گره لیست که اشاره‌گرش `null` است <b>"Tail"</b> یا "دم" می‌گویند.

### شکل شماتیک
```
Head                          Tail
  |                             |
  v                             v
[10|Next] -> [20|Next] -> [30|Next] -> Null
```

##  عملیات روی لیست پیوندی

### عملیات درج

تصور کنید که می‌خواهیم گره B (گره جدید) را بین گره A (گره چپ) و گره C (گره راست) درج کنیم.
```
     A(Left node)                              C(Right node)
          |                                           |
          v                                           v
    [Data|Next(C)] ----------------------------> [Data|Next]



                            [Data|Next]

                                ^
                                |
                            B(New node)
```
در این صورت B باید به C به عنوان next اشاره کند:

`B.next -−> C;`
```
     A(Left node)                              C(Right node)
          |                                           |
          v                                           v
    [Data|Next(C)] ----------------------------> [Data|Next]

                                                     ^
                                                     |
                         [Data|Next(C)]--------------/

                                ^
                                |
                            B(New node)
```
حالا گره سمت راست (A) باید به گره جدید (B) اشاره کند:

`A.next -−> B;`
```
     A(Left node)                              C(Right node)
          |                                           |
          v                                           v
    [Data|Next(B)]                               [Data|Next]
            |
            |                                         ^
            |                                         |
            \-----------> [Data|Next(C)]--------------/

                                ^
                                |
                            B(New node)
```
بدین ترتیب گره جدید در میان دو گره قبلی قرار می‌گیرد. لیست جدید به صورت زیر خواهد بود:
```
     A(Left node)                                    C(Right node)
          |                                                |
          v                                                v
    [Data|Next(B)]---------> [Data|Next(C)]---------> [Data|Next]

                                   ^
                                   |
                               B(New node)
```
اگر بخواهیم گره‌ای را در ابتدای لیست اضافه کنیم نیز مراحل مشابهی را طی می‌کنیم، فقط به‌جای گره چپ، head را قرار می‌دهیم.

 همچنین زمانی که می‌خواهیم گره‌ای را در انتهای لیست درج کنیم، گره جدید به یک مقدار null اشاره خواهد کرد.
<br>
<br>
### عملیات حذف
ابتدا گره هدف که می‌خواهیم حذف کنیم را با استفاده از الگوریتم‌های جستجو می‌یابیم.

برای مثال می‌خواهیم گره B را از میان A و C حذف کنیم:
```
     A(Left node)           B(Target node)           C(Right node)
          |                        |                       |
          v                        v                       v
    [Data|Next(B)]---------> [Data|Next(C)]---------> [Data|Next]
```
گره چپ (A) باید به گره راست B (C یا همان B.next) اشاره کند:

`A.next −-> C;`
```
     A(Left node)           B(Target node)           C(Right node)
          |                        |                       |
          v                        v                       v
    [Data|Next(C)]          [Data|Next(C)]---------> [Data|Next]
             |                                            ^
             |                                            |
             \____________________________________________/
```
با این کار پیوندی که از گره چپ (A) به گره هدف (B) وجود داشت از بین می‌رود.

 ما می‌توانیم گره حذف شده (B) را در حافظه نگه داریم ولی حالا که نیازی به آن نداریم می‌توانیم به سادگی آن را به طور کامل پاک کنیم و حافظه اشغال شده را آزاد کنیم:

`Delete(node B);`
```
     A(Left node)            C(Right node)
          |                         |
          v                         v
    [Data|Next(C)] ----------> [Data|Next]
```

##  انواع لیست‌ پیوندی
چند مدل لیست پیوندی داریم که اینجا می‌بینیم:
### لیست پیوندی یک‌طرفه (Singly Linked List)

```
Head
  |
  v
[10|Next] -> [20|Next] -> [30|Next] -> None
```
 نوع عادی و اولیه لیست پیوندی که حداقل به دو قسمت داده و اشاره‌گر نیاز دارد و در بالا توضیح داده شد.


### لیست پیوندی دو طرفه (Doubly Linked List)

```
None <- [Prev|10|Next] <-> [Prev|20|Next] <-> [Prev|30|Next] -> None
```
گره های این مدل لیست پیوندی هم به عنصر بعدی‌شان اشاره می‌کنند، هم به قبلی.

در واقع با استفاده از یک اشاره‌گر دیگر (Prev) به عضو قبلی نیز اشاره می‌کنند. پس به عقب هم می‌توان پیمایش کرد، ولی برای ذخیره اشاره‌گر اضافی به حافظه بیشتری نیاز است.

 لیست‌های پیوندی دو طرفه انعطاف‌پذیری بیشتری دارند و
عملیات درج و حذف عناصر در وسط لیست به دلیل وجود اشاره‌گر به گره قبلی، سریع‌تر انجام می‌شود.<br>
 بیشترین کاربرد این نوع لیست پیوندی در پیاده‌سازی گراف‌هاست.


---

### لیست پیوندی حلقوی (Circular Linked List)

```
     ___________________________
    /                           \
    |                           |
    v                           |
[10|Next] -> [20|Next] -> [30|Next]

```
این لیست پیوندی ساختار دایره‌ای دارد. در واقع، اشاره‌گر  آخرین گره به گره اول اشاره می‌کند و یک ساختار دایره‌ای را تشکیل می‌دهد.

 همچنین پیمایش مداومی دارد و می‌توان از هر گره‌ شروع کرده و به همان گره بازگشت.<br>
 کاربرد لیست‌های پیوندی حلقوی در پیاده‌سازی صف‌های حلقوی و مدیریت حافظه است.

این نوع لیست پیوندی می‌تواند هم به صورت یک طرفه، و هم دو طرفه باشد.

<br>


##  ضمیمه 1 - مزایا و معایب
<details>
<summary> نمایش </summary>

### ساختار حافظه
**آرایه:** داده‌ها به‌صورت پشت سر هم ذخیره می‌شوند و اندازه ثابت است.<br>
**لیست پیوندی:** گره‌ها می‌توانند در هر جای حافظه باشند و اندازه پویا است.

 >⚠️نکته: لیست پیوندی به دلیل ذخیرهٔ اشاره‌گر، نسبت به آرایه حافظهٔ بیشتری اشغال می‌کند.

### سرعت دسترسی

**آرایه:** دسترسی مستقیم و بسیار سریع به هر عنصر: (1)O<br>
**لیست پیوندی:** نیاز به پیمایش: O(n)



### انعطاف‌پذیری
**آرایه:** ساختار ثابت و غیر قابل تغییر، انعطاف‌پذیری کم.<br>
**لیست پیوندی:** ساختار پویا و قابل تغییر، انعطاف‌پذیری بالاتر.


### پیمایش
**آرایه:** به هر شکل دلخواه با سرعت بالا.<br>
**لیست پیوندی:** در لیست‌های پیوندی یک‌طرفه امکان پیمایش به عقب وجود ندارد.

</details>
<br>

##  ضمیمه 2 - کاربرد در زندگی واقعی
<details>
<summary> نمایش </summary>

### تاریخچه مرورگر وب (Back/Forward Button)

 وقتی شما در مرورگر خود از صفحه‌ای به صفحه دیگر می‌روید، آدرس هر صفحه به عنوان یک "گره" در یک **لیست پیوندی دوطرفه** ذخیره می‌شود.
- **گره فعلی:** صفحهای که هم اکنون می‌بینید.
- **دکمه Back (عقب):** اشاره‌گر را به گره قبلی در لیست منتقل می‌کند.
- **دکمه Forward (جلو):** اشاره‌گر را به گره بعدی در لیست منتقل می‌کند.

### پخش کننده موسیقی (Playlist)

 هر آهنگ یک گره است که حاوی داده‌های آهنگ و یک اشاره‌گر به آهنگ بعدی است.
- **قابلیت پخش متوالی:** پخش کننده به راحتی از یک آهنگ به آهنگ بعدی می‌رود.
- **حذف و اضافه کردن آهنگ:** فقط با تغییر اشاره‌گرهای گره‌های قبلی و بعدی انجام می‌شود.


### سیستم Undo / Redo در نرم‌افزارها

در نرم‌افزارهایی مانند Word و Photoshop:
 هر عمل کاربر به عنوان یک گره در **لیست پیوندی دوطرفه** ذخیره می‌شود.
- **دکمه Undo:** اشاره‌گر را به گره قبلی منتقل می‌کند.
- **دکمه Redo:** اشاره‌گر را به گره بعدی برمی‌گرداند.


### پیاده سازی ساختار داده‌ها، مثل:
- صف
- پشته
- بخش‌هایی از جدول هش

### نکته:
برخلاف تصور لیست‌های پایتون از لیست پیوندی استفاده نمی‌کنند و در واقع آرایه‌های پویا یا همان `Dynamic Arrays` هستند.
</br>
</details>



<br>
<br>
<br>
<br>


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

<br>

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

### لیست پیوندی حلقوی دو طرفه با Loop در C
<details>
<summary>نمایش</summary>

شامل:
- insert_head (درج در ابتدای لیست)
- insert_tail (درج در انتهای لیست)
- insert_position (درج در ایندکس مشخص)
- delete_head (حذف ابتدای لیست)
- delete_tail (حذف انتهای لیست)
- view (نمایش کل لیست)

```C
#include<stdio.h>
#include<stdlib.h>


struct Node{
    int value;
    struct Node* next;
    struct Node* prev;
};


void insert_tail(struct Node** head, int value){
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode -> value = value;

    if (*head == NULL){
        *head = newNode;
        newNode -> next = newNode;
        newNode -> prev = newNode;
        return;
    }

    struct Node* trace = *head;
    while (trace -> next != *head){trace = trace -> next;}

    newNode -> next = *head;
    newNode -> prev = trace;
    trace -> next = newNode;
    (*head) -> prev = newNode;
}


void insert_head(struct Node** head, int value){
    if (*head == NULL){insert_tail(head, value);return;}

    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode -> value = value;

    newNode -> next = *head;
    newNode -> prev = (*head) -> prev;
    (*head) -> prev -> next = newNode;
    (*head) -> prev = newNode;
    (*head) = newNode;
}


void insert_position(struct Node** head, int value, int position){
    if (position < 1){printf("Invalid position\n");return;}
    if (position == 1){insert_head(head, value);return;}
    if (*head == NULL){printf("Invalid position\n");return;}

    struct Node* trace = *head;
    for (int i = 1; i < position - 1; i++){
        trace = trace -> next;
        if (trace == *head){
            printf("Invalid position\n");
            return;
        }
    }

    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode -> value = value;

    newNode -> prev = trace;
    newNode -> next = trace -> next;
    trace -> next -> prev = newNode;
    trace -> next = newNode;
}


void delete_head(struct Node** head){
    if (*head == NULL){printf("List is already empty!\n");return;}
    struct Node* temp = *head;
    if ((*head) -> next == *head){*head = NULL;}
    else {
        (*head) -> prev -> next = (*head) -> next;
        (*head) -> next -> prev = (*head) -> prev;
        *head = (*head) -> next;
    }
    free(temp);
}


void delete_tail(struct Node** head){
    if (*head == NULL){printf("List is already empty!\n");return;}
    if ((*head) -> next == *head){
        struct Node* temp = *head;
        *head = NULL;
        free(temp);
    }
    else {
        struct Node* trace = *head;
        while (trace -> next != *head){trace = trace -> next;}
        trace -> prev -> next = trace -> next;
        trace -> next -> prev = trace -> prev;
        free(trace);
    }
}


void view(struct Node** head){
    if (*head == NULL){printf("Empty!\n");return;}

    struct Node* trace = *head;
    printf("%d -> ", trace -> value);
    trace = trace -> next;

    while (trace != *head){
        printf("%d -> ", trace -> value);
        trace = trace -> next;    
    }

    printf("head\n");
}


int main() {
    struct Node* head = NULL;

    insert_head(&head, 3);
    insert_tail(&head, 4);
    insert_head(&head, 2);
    insert_tail(&head, 5);
    insert_head(&head, 1);
    insert_tail(&head, 6);
    view(&head);

    insert_position(&head, 7, 7);
    insert_position(&head, 0, 1);
    view(&head);

    delete_head(&head);
    delete_head(&head);
    delete_tail(&head);
    delete_tail(&head);
    view(&head);

    return 0;
}
```
</details>


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

</details>


<br>
<br>
<br>
<br>
<br>


# سوالات طبقه بندی شده لیست پیوندی  


### سوال 1
تفاوت آرایه و لیست پیوندی را توضیح دهید.

**پاسخ:**  
 آرایه: طول ثابت دارد درج و حذف نیاز به جابه‌جایی دارد. برای جست‌وجو و مرتب‌سازی مناسب‌تر است.  
 لیست پیوندی: طول پویا دارد درج و حذف تنها با تغییر آدرس‌ها انجام می‌شود. جست‌وجو سخت‌تر است چون باید پیمایش شود.

---

### سوال 2
لیست پیوندی چیست و چگونه تعریف می‌شود؟

**پاسخ:**  
لیست پیوندی مجموعه‌ای از گره‌ها (node) است که هر گره شامل داده و آدرس گره بعدی می‌باشد. اولین گره توسط متغیر **head** نگهداری می‌شود.

---

### سوال 3
یک لیست پیوندی یک‌طرفه با 1000 گره ایجاد کنید که اعداد 1 تا 1000 را ذخیره کند.

**پاسخ:**  
 تعریف ساختار گره با دو فیلد: داده و اشاره‌گر به گره بعدی.  
 ایجاد head و اشاره به اولین گره.  
 با حلقه از 1 تا 1000 گره‌ها ساخته می‌شوند و به هم لینک می‌شوند.  
 گره آخر به null اشاره می‌کند.  

### زبان C:
```c
struct node {
    int data;
    struct node *next;
};

struct node *head, *x, *y;

head = (struct node*)malloc(sizeof(struct node));
head →
 data = 1;
y = head;

for (int i = 2; i <= 1000; i++) {
    x = (struct node*)malloc(sizeof(struct node));
    x →
 data = i;
    y →
 next = x;
    y = x;
}
y →
 next = NULL;
```

### زبان python:
```python
class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

head = Node(1)
y = head

for i in range(2, 1001):
    x = Node(i)
    y.next = x
    y = x
```
---

### سوال 4
روش درج یک گره بعد از گره مشخص x را توضیح دهید.

**پاسخ:**  
 گره جدید ساخته می‌شود.  
 لینک گره جدید برابر لینک گره x قرار داده می‌شود.  
 لینک گره x برابر گره جدید قرار داده می‌شود.

---

### سوال 5
روش حذف یک گره مشخص x را توضیح دهید.

**پاسخ:**  
 پیمایش تا رسیدن به گره قبل از x.  
 لینک گره قبل از x برابر لینک گره x قرار داده می‌شود.  
 گره x آزاد (delete/free) می‌شود.

---

### سوال 6
روش درج در ابتدای لیست را توضیح دهید.

**پاسخ:**  
 گره جدید ساخته می‌شود.  
 لینک آن برابر head قرار داده می‌شود.  
 head برابر گره جدید قرار داده می‌شود.

---

### سوال 7
لیست حلقوی چیست و درج در ابتدای و انتهای آن چگونه انجام می‌شود؟

**پاسخ:**  
 لیست حلقوی: لینک گره آخر به اولین گره اشاره می‌کند.  
 درج در ابتدای لیست حلقوی: گره جدید ساخته می‌شود لینک آن برابر head قرار داده می‌شود سپس لینک گره آخر برابر گره جدید می‌شود.  
 درج در انتهای لیست حلقوی: پیمایش تا گره آخر انجام می‌شود لینک گره آخر برابر گره جدید قرار داده می‌شود و لینک گره جدید برابر head می‌شود.

---

### سوال 8
 
لیست دوطرفه چیست و درج و حذف در آن چگونه انجام می‌شود؟


**پاسخ:**  
 هر گره شامل داده اشاره‌گر به گره بعدی (Right) و اشاره‌گر به گره قبلی (Left) است.  
 درج: گره جدید ساخته می‌شود اشاره‌گرهای قبل و بعد تنظیم می‌شوند.  
 حذف: اشاره‌گرهای گره‌های قبل و بعد از x تغییر داده می‌شوند تا x از لیست حذف شود.

---

### سوال 9
اگر متغیر L یک اشاره‌گر به head، و لیست پیوندی حلقوی شامل اعداد 1 تا 6 باشد، خروجی قطعه کد زیر را بنویسید:
```python
while(Link(L) != L){
    Link(L) = Link(link(L));
    L = Link(L);
}
print(data(L))
```

**پاسخ:**
این سوال بیانگر مسئله Josephus می‌باشد. اعداد به شکل یک در میان حذف می‌شوند تا عدد 5 باقی می‌ماند:
```
1, 2, 3, 4, 5, 6
1, 3, 5
1, 5
5
```

### سوال 10
مسئله Josephus را توضیح دهید و روش حل آن را بیان کنید. 

**پاسخ:**  
 افراد در یک حلقه قرار دارند و به صورت چرخشی حذف می‌شوند.  
 راه‌حل: عدد داده شده را به باینری تبدیل کرده و یک چرخش چپ انجام دهید.  
 
 مثال:  
اگر n = 6 باشد:<br>
<div dir="ltr" align="center">
 6 = (110)<sub>2</sub> → Rotation → (101)<sub>2</sub> = 5.  
 </div>

پس آخرین عدد باقی‌مانده 5 است.  
<br>

**فرمول کلی:**
$$
2 \times (n - 2^m) + 1
$$  

که m<sup>2</sup> بزرگترین توان 2 کوچکتر از n است .



<br><br><br><br>
# نمونه سوالات 4 گزینه‌ای لیست پیوندی 
### سوال 1
 
 فرض کنید یک لیست پیوندی یک‌طرفه داریم.
 می‌خواهیم گره دوم از انتها یعنی گره ماقبل آخر را حذف کنیم. بهترین روش برای انجام این کار چیست؟ (ارشد علوم کامپیوتر 1402)  
> 1 )  تبدیل لیست به آرایه و حذف گره  

> 2 ) حرکت دادن یک اشاره‌گر تا انتهای لیست و شمارش گره‌ها

> 3 ) حرکت دادن یک اشاره‌گر با شمارنده تا موقعیت مطلوب  

> 4 ) استفاده از دو اشاره‌گر که یکی دو گره جلوتر از دیگری است.


 پاسخ صحیح: گزینه 4  

#### توضیح :
 در لیست پیوندی یک‌طرفه دسترسی مستقیم به طول لیست یا عناصر انتهایی نداریم.  
    برای حذف گره دوم از انتها بهترین روش استفاده از **دو اشاره‌گر (Two Pointer Technique)** است:   
   اشاره‌گر اول را دو گره جلوتر از اشاره‌گر دوم قرار می‌دهیم.  
   سپس هر دو اشاره‌گر را همزمان حرکت می‌دهیم تا اشاره‌گر اول به انتهای لیست برسد.  
    در این لحظه اشاره‌گر دوم دقیقا روی گره ماقبل آخر قرار دارد و می‌توان آن را حذف کرد. 

---

### سوال 2  
 چه تعداد از گزاره های زیر درست است ؟

الف) زمان پیدا کردن یک عنصر در یک لیست پیوندی مرتب باعضوی $\theta(n)$
 است.                                       
ب) زمان پیدا کردن یک عنصر در یک آرایه نامرتب با عضوی  $ \theta(n) $ است.  
ج) زمان پیدا کردن یک عنصر در یک آرایه مرتب با n عضوی $ \theta(logn) $ است.  

> 1 ) 3 

> 2 ) 2  

> 3 ) 1 

> 4 ) 0
 

پاسخ صحیح: گزینه 1  

####  توضیح :

همه ی موارد درست هستند.

---



### سوال 3


 یک آرایه n‌ تایی داریم بطوری که هر خانه آرایه حاوی یک لیست پیوندی یک‌طرفه از n عدد صعودی است.
 همچنین همه اعداد هر خانه آرایه کوچکتر از همه اعداد خانه بعدی آرایه است.
   زمان لازم برای جستجو یک عدد در میان این 
      $n^2$      عدد از چه مرتبه ای است ؟  


> 1 ) $n log n$  

> 2 ) $log n$  

> 3 ) $n$  

> 4 ) $n^2$

پاسخ صحیح: گزینه 3 

---

### سوال 4 

 حداقل حافظه کمکی لازم برای دو عمل زیر به ترتیب از 
 **راست به چپ**
از چه مرتبه‌ای است؟
( ارشد علوم کامپیوتر 1401 )

برعکس کردن یک لیست پیوندی یک طرفه$ n$ عضوی

برعکس کردن یک لیست پیوندی دو طرفه$ n$ عضوی 


> 1 ) $n$, $n$

> 2 ) $n$, $1$

> 3 ) $1$, $n$

> 4 ) $1$ ,$1$

پاسخ صحیح: گزینه 4 


---

### سوال 5 

 فرض کنید $x = (x_1, x_2, \dots, x_n)$ و $y = (y_1, y_2, \dots, y_m)$ دو لیست پیوندی خطی ساده باشند. مرتبه زمانی الگوریتمی که دو لیست را در لیست $z$ ترکیب می‌کند کدام است؟( ارشد علوم کامپیوتر 1398 و مهندسی کامپیوتر 1404 )  

$$
z = 
\begin{cases}
(x_1, y_1, x_2, y_2, \dots, x_m, y_m, x_{m+1}, \dots, x_n) & \text{اگر } m \leq n \\
(x_1, y_1, x_2, y_2, \dots, x_n, y_n, y_{n+1}, \dots, y_m) & \text{اگر } m > n
\end{cases}
$$

> 1 ) $O(mn)$  

> 2 ) $O(m + n)$  

> 3 ) $O(\max(m, n))$  

> 4 ) $O(\min(m, n))$

پاسخ صحیح: گزینه 4 


---

### سوال 6

 الگوریتم زیر چه عملی روی لیست پیوندی با آدرس شروع P انجام میدهد؟( ارشد علوم کامپیوتر 1397)
   
```c
list * listravel(list * P)
{
         list * h
    if(P == null)or(P → link == null)
             return(P)
     h = listravel (P → link)
     P → link → link = P
     P → link = null
     return h
}
```
>1 ) لیست پیوندی را تغییر نمی‌دهد  

>2 ) لیست پیوندی را برعکس می‌کند  

>3 ) اشاره‌گر انتهای لیست را به ابتدا می‌برد  

>4 ) اشاره‌گر ابتدای لیست را به انتها می‌برد  

پاسخ صحیح: گزینه 2 


---

### سوال 7
 
اگر s آدرس شروع یک لیست متصل غیرتهی باشد الگوریتم زیر با فراخوانی (null , s , s = w) چه عملی روی این لیست انجام می‌دهد؟( ارشد علوم کامپیوتر 1396)
```c
w(m, t, s){
     if (t → link != null){
             s = w(t, t → link, s)
     }
     else  s = t
     t → link = m
     return (s)
}
```
>1  ) لیست پیوندی را تغییر نمی‌دهد  لیست متصل را دایره‌ای می‌کند.   

>2  ) لیست متصل را برعکس می‌کند.   

>3  )   لیست متصل را به دو لیست تبدیل می‌کند.   

>4  )  لیست متصل را به گره‌های بدون اتصال تبدیل می‌کند.   

پاسخ صحیح: گزینه 2 


---

### سوال 8 

فرض کنید a و b اشاره گر به گره وسط به ترتیب در لیست های `L1` و `L2` هستند.
با فرض اینکه `L1` و `L2` لیست های پیوندی یکطرفه دایره ای هستند. 
فراخوانی `change(a,b)` چه تغییراتی بر روی این لیست ها پدید می آورد؟

```c
void change (link *a, link *b){
  ink *temp = a → next;
  a → next = b → next;
  b → next = temp;
}
```
>1  ) دو لیست از تعویض نیمه دوم لیست ها با یکدیگر به دست می اید .   

>2  ) یک لیست پیوندی دایره ای از اتصال لیست ها به دست می اید .   

>3  )در عمل باعث میشود لیست های L1 , L2  با یکدیگر جابجا شوند .   

>4  ) چهار لیست پیوندی دایره ای جدید به وجود می ایند که هر یک شامل نیمه ای از لیست های اولیه است .    

پاسخ صحیح: گزینه 3 


---

### سوال 9 

فرض کنید یک لیست پیوندی یک‌طرفه از $n$ گره داریم 
و شما می‌خواهید گره‌ای را که در موقعیت $n  \frac{3}{4}$ قرار گرفته پیدا کنید 
اما مقدار $n$ را نمی‌دانیم. فرض کنید $n$ مضربی از ۴ است. کدام‌یک از گزینه‌ها ما را به نتیجه نمی‌رساند؟
(ارشد مهندسی کامپیوتر 1404)
> 1 ) ابتدا طول لیست را به طور کامل محاسبه کنید سپس به اندازه $\frac{3n}{4}$ از ابتدا به جلو حرکت کنید تا گره موردنظر را پیدا کنید.  
> 2 ) با دو اشاره‌گر که یکی از ابتدا با سرعت سه گره و دیگری از انتها (پس از پیدا کردن گره انتهایی) با سرعت یک گره حرکت کنند و در لحظه رسیدن به یکدیگر نتیجه حاصل خواهد شد.  
> 3 ) ابتدا طول لیست را بطور کامل محاسبه کنید سپس از دو اشاره‌گر استفاده کنید. یکی را از ابتدای لیست و دیگری را در گره $\frac{n}{4}$ تنظیم کنید. با سرعت یک گره حرکت کنید تا گره جلوتر به انتها برسد تا به هدف برسیم.  
 > 4 )    با دو اشاره‌گر که یکی با سرعت یک گره 
 و دیگری با سرعت دو گره حرکت می‌کند. به نیمه می‌رسیم یک گره جلو بودیم و اشاره‌گر دوم که به انتها رسیده را مجدد برابر اشاره‌گر اول قرار خواهیم داد تا مجدد عمل انجام شود و نتیجه حاصل شود.


پاسخ صحیح: گزینه 2 


---

### سوال 10 

 یک لیست خطی یک‌طرفه با دو اشاره‌گر F و R که به ترتیب به عنصر اول و آخر لیست اشاره می‌کنند پیاده‌سازی شده است. هزینه‌ی کدام‌یک از اعمال (دولتی 80 )زیر وابسته به تعداد عناصر لیست است؟
 

> 1 ) حذف اولین عنصر   

> 2 ) حذف اخرین عنصر  

> 3 ) درج یک عنصر در انتهای لیست  

> 4 ) درج یک عنصر در ابتدای لیست  

پاسخ صحیح: گزینه 2 

####  توضیح :
برای حذف آخرین عنصر باید لیست پیمایش شود تا به گره ماقبل اخر برسیم و link ان را تهی کنیم . در بقیه گذینه ها طول لیست اهمیت ندارد.

---

### سوال 11 

زیر برنامه g بر رویه لیست پیوندی یکطرفه کدام عمل را 
 انجام می دهد؟

```c
Procedure g(Var Start:Nodeptr);
Var
     p,q,r:Nodeptr;
begin
     p:=start;
     q:=Nil;
     while p<> nil do 
     begin
          r:=q; q:=p;
          p:=p^.Link;
          q^.Link;=r;
     end;    
     Start:=q;
end;
```
> 1 )پیمایش لیست  

> 2 ) حذف کردن لیست  

> 3 )معکوس کردن لیست  

> 4 ) مرتب کردن لیست 

پاسخ صحیح: گزینه 3 

####  توضیح :
زیر برنامه را روی یک لیست با دو گره ازمایش کنید.(این رویه را حفظ کنید و خاطرتان باشد برای معکوس کردن لیست به صورت بازگشتی 3 اشاره گر کمکی باید تعریف کرد)

---

### سوال 12

 تابع زیر چه عملی انجام می دهد ؟ (با فرض اینکه نوع list اشاره گر است )

  ```c

list x(list L)
{     list m,t;
     m=NULL;
     while(L) {

    t=m; m=L;
    L=L → link;
    m → link = t; }
    return m;}
    
```    
> 1 )محل دو عنصر در لیست » را جابجا می کند. 

> 2 ) لیست پیوندی » را معکوس می کند.  

> 3 )عنصری را از لیست L جابجا می کند. 

> 4 ) لیست L را مرور می کند. 

پاسخ صحیح: گزینه 2 

####  توضیح :

مشابه سوال بالا است .

---

### سوال 13 

 تابع زیر چه عملی را انجام می دهد ؟ توضیح اینکه List نشان دهنده لیستی از اعداد بوده و منظور از تابع Head تابعی است که مقدار اولین عنصر در لیست را برمیگرداند و تابع Tail لیستی حاوی همه عناصر لیست ورودی به استثنای اولین عنصر را برمیگرداند.
 (دولتی 76 ) مکان های لیست را از مکان 1 در نظر بگیرید :

```c
function what (L:List): integer;
begin
     if L=nil then
          what:=0
     else 
         if Tail(L)/=nil then
             what :=(Head(L) + what (Tail(Tail(L))))
     else
             what := Head(L)
end;
```
>1 )تعداد عناصر را برمیگرداند 

>2 ) مجموع عناصر در مکان های فرد لیست ورودی را برمیگرداند.  

>3 )تعداد عناصر در مکان های فرد لیست ورودی را برمیگرداند.

>4 )مجموع عناصر لیست ورودی را برمیگرداند. 
       
پاسخ صحیح: گزینه 2 

####  توضیح :
بار اول:
what(1):= Head(1) + what(3) = 10 + 30 = 40

what(3) = Head(3) = 30

---
                   
### سوال 14
  میخواهیم تغییراتی در یک لیست پیوندی اعمال کنیم که عمل افزودن عنصر ابتدا و یا انتهای لیست با عملیاتی از مرتبه $(O(1))$  قابل انجام باشد. لیست پیوندی را ....
(علوم کامپیوتر 79 )

>1 )حلقوی میکنیم . 

>2 )دو طرفه میکنیم.  

>3 )حلقوی میکنیم و ادرس اخرین عنصر را برای دسترسی به لیست ذخیره میکنیم.

>4 )معکوس میکنیم. 

پاسخ صحیح: گذینه 3 

####  توضیح :
در لیست حلقوی اگر بجای ذخیره ادرس اولین گره ادرس اخرین گره را ذخیره کنیم افزودن عنصر به اخر یا اول لیست نیازی به پیمایش ندارد و با $ (O(1)) $ انجام میشود.

---

### سوال 15 

 الگوریتم زیر چیست ؟ 

```c
procedure print (L: listpointer);
 begin
     if (L<>nil) then begin
        if tag(L)=0 then
            write (data(L))
         else
     print (data(L));
     print (Link(L));
     end
 end;
```
>1 )پیمایش لیست حلقوی  

>2 )پیمایش لیست عمومی  

>3 )شمارش تعداد گره های لیست عمومی 

>4 )حذف گره های لیست عمومی 

پاسخ صحیح: گزینه 2 

####  توضیح :
رویه به صورت بازگشتی لیست عمومی را پیمایش میکند.

---

### سوال 16 

اگر سه اشاره گر p1 و p2 و p3 روی لیست L حرکت کنند و سه تابع First و Next و end مقدار منطقی متناسب را برمیگرداند, تعداد دفعات اجرای تابع first برحسب n (تعداد عناصر لیست) چیست ؟
(دولتی 81)

```c
P1:=First(L);
while P1<>end(L) do begin 
    P2:=P1;
    while P2<>end(L) do begin
      P2:=Next(P2,L);
      P3:=First(L);
      while P3<>P2 do P3:=Next(P3,L)
    end;
    P1:=Next(P1,L);
end;
```
>1)$$\frac{(n - 1)^2}{2} + 1$$

>2)$$(n - 1)^2 + 1$$

>3)$$\frac{n}{2}(n - 1) + 1$$

>4)$$\frac{n}{2}(n + 1)$$


پاسخ صحیح: گزینه 3 

####  توضیح :
حلقه while سوم هیچ تاثیری در فراخوانی first ندارد. حلقه while دوم بار اول n-1 بار، بار دوم n-2 بار و... اجرا می شود: 
1 + 2 + 3 + ... + (n-1) = $ n(n-1)/2 $
و چون تابع first یک بار در ابتدای برنامه زیر فراخوانی می شود : 
$ n(n-1)/2 + 1 $

<br>

---
#### نویسندگان

نویسنده | مبحث | گیتهاب
-------|---------|--------
آرمان کیانی | کد و مثال‌ | https://github.com/AriK822
کاترین پرویش | نمونه سوال | https://github.com/katrinparvish
سجاد رنجبران | درسنامه | https://github.com/Sajjad4297
