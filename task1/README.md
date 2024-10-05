# Assignment 1

# 1. GPT-NeoX

В данной статье будем рассматривать GPT-NeoX open-source AI model. 

Данная модель состоит из следующих важных компонент:

- Embedding Layer
- Transformer blocks
- Final Linear Layer and Softmax

## Embedding Layer

В общей случае этот слой преобразует токены в многомерные векторы.

Каждый токен представлен в виде однократного вектора длины $V$, а матрица имеет размер $V \times d$, где $d$ - размерность модели(embedding size).

Для $n$ токенов сложность: $O(n \cdot d)$

## Transformer blocks

Обычно трансформерные блоки включает в себя: Self-Attention, Feed-Forward Layer, Layer Normalization.

### Self-Attention 

Тут происходит взвешивание сумм между всеми парами токенов.

Каждый токен проецируется в векторы запроса, ключа и значения посредством линейных преобразований. 

Для $n$ токенов и модели размерностью $d$ сложность: $O(n \cdot d^2)$.

Далее вычисляется скалярное произведение между запросом и ключевыми векторами, в результате чего получается оценочная матрица размера: $n \times n$. Таким образом для модели размерностью $d$ сложность: $O(n^2 \cdot d)$.

Далее применяется функция softmax, а полученные значения используются для вычисления взвешенной суммы векторов значений. Для этого умножается attention матрица ($n \times n$) на матрицу значений ($n \times d$). Таким образом сложность: $O(n^2 \cdot d)$.

Общая сложность для Self-Attention: $O(n \cdot d^2 + n^2 \cdot d)$.

### Feed-Forward Layer 

В общем случае данный слой представляет веса, которые обрабатываются во время обучения, и точно такая же матрица применяется к каждой соответствующей позиции токена. Основная цель данного слоя - обработать выходные данные одного уровня внимания таким образом, чтобы лучше подогнать входные данные для следующего attention layer.

Feed-Forward Layer состоит из двух линейных уровней с функцией активации между ними. Первый слой увеличивает размерность с $d$ до $4d$, а второй проецирует еог обратно с размерностью $d$.

Таким образом, общая сложность для Feed-Forward Layer: $O(n \cdot d^2)$.

### Layer Normalization

Данный слой нормализует входные данные, в результате чего получаем данные, которые имеют последовательное распределение. Также это уменьшает проблему внутреннего смещения ковариат, которая может возникнуть во время обучения.

Нормализация слоев применяется дважды в каждом блоке преобразователя (перед Self-Attention и перед Feed-Forward Layer). В данном случае нормализация представляется как поэлементная операция с линейной сложностью по длине последовательности и embedding size($d$).

Сложность: $O(2 \cdot n \cdot d^2)$ = $O(n \cdot d^2)$.

## Final Linear Layer and Softmax

Данный слой сопоставляет выходные векторы с словарным пространством и вычисляет вероятности для следующего токена. После прохождения через все трансформерные блоки выходные данные проецируются в соответствии с размером словаря $V$. Затем применяется softmax для получения вероятностей для каждого токена.

Так сложность для $n$ токенов и словаря размером $V$: $O(n \cdot d \cdot V)$.

Для Softmax сложность: $O(n \cdot V)$.

Общая сложность: $O(n \cdot d \cdot V)$ + $O(n \cdot V)$ = $O(n \cdot d \cdot V)$.

---

Общая сложность для одного Transformer block: $O(n \cdot d^2)$ + $O(n^2 \cdot d)$.

Учитывая, что модель состоит из $N$ блоков, то сложность для forward propogation: $O(N (n \cdot d^2)$ + $O(n^2 \cdot d))$.

Однако необходимо учитывать backpropogation, что удваивает сложность.

# 2. PageRank Algorithm

Алгоритм PageRank включает в себя итеративный процесс, который вычисляет ранжирование веб-страниц на основе структуры ссылок. Его можно представить в виде задачи умножения разреженной матрицы на вектор. 

Введём некоторые обозначения:
- $N$: Количество веб-страниц
- $L$: Количество ссылок между страницами
- $I$: Количество итераций, необходимых для схождения

Для PageRank каждая итерация требует обработки ссылок между страницами. Поскольку график разрежен (большинство страниц ссылаются только на несколько других), сложность каждой итерации составляет приблизительно: $O(I \cdot L)$ = $O(I \cdot N)$ (так как $L$ ~ $N$).

Пусть $N \approx 10^{11}$, $L \approx 10^{12}$, $I \approx 100$. 

Тогда сложность будет: $O(100 \cdot 10^{12}) = 10^{14}$. 

Пусть система может выполнить $1 TOPS = 10^{12}$ операций в секунду.

Тогда $Time = \dfrac{10^{14}}{10^{12}} = 100$ сек. 

Предполагая, что у нас идеальный параллелизм и эффективность, необходимо 100 сек.  для полной итерации PageRankом. 