#include <QCoreApplication>
#include <QQueue>


QStringList htmlLines = {
    "<!DOCTYPE html>",
    "<html lang=\"en\">",
    "<head>",
    "<meta charset=\"UTF-8\">",
    "<title>Short poems</title>",
    "</head>",
    "<body>",
    "Hi!",
    "<p>What goes up when",
    "the rain comes down?</p>",
    "<b>Who is your best friend?</b>",
    "<p>What do you call a snowman in the summer?</p>",
    "<i>What is your favorite movie?</i>",
    "<p>Two little birds",
    "Sitting on a wall,",
    "One called Peter,",
    "One called Paul.</p>",
    "<tt>When does the sun rise in the morning?</tt>",
    "<p>Where is the nearest coffee shop?</p>",
    "<ins> Why do people procrastinate?</ins >",
    "<p>How do you make chocolate chip cookies?</p>",
    "<code>Whose idea was it to have a picnic?</code>",
    "</body>",
    "</html>"
}; //test data for parsing html

QString passwords = "a F1#, 2%wl&I3lEI^!l, ABd1234@1, 908I4#1_gU, 2We3345, $0o0i00lII!1"; //test data for password check

QString kitNumbers(int in) //task 1
{
    if (in <= 0) return "NO";
    QString res;
    QQueue<int> myQueue;

    auto printQueue = [](const QQueue<int>& q) {
        for (int num : q) {
            qDebug() << num;
        }
        qDebug();
    };

    // Лямбда для вычисления суммы элементов
    auto sum = [](const QQueue<int>& q) -> long long {
        long long s = 0;
        for (int i : q) {
            s += i;
            if (s > INT_MAX) break; // Если сумма уже превышает INT_MAX
        }
        return s;
    };

    // разбиваем число на цифры
    QString inStr = QString::number(in);
    for (const QChar &i : inStr) {
        int digit = i.toLatin1() - '0';
        myQueue.enqueue(digit);
        res += " " + QString(i);
        // printQueue(myQueue);
    }

    long long curSum = 0;
    while (curSum < in) {
        // printQueue(myQueue);
        curSum = sum(myQueue); //я поставил ограничение на переполнение INT_MAX
        if (curSum > INT_MAX) { // Проверка на переполнение суммы
            return "NO";
        }
        myQueue.enqueue(static_cast<int>(curSum)); // Приводим к int, так как curSum <= INT_MAX
        res += " " + QString::number(curSum);
        myQueue.dequeue();
    }
    if (curSum != in) {
        return "NO";
    }

    return res.mid(1); // Убираем начальный пробел
}

QString parsing(QStringList in) //task 2
{
    QStringList tmp;
    QString res;
    bool isP = false;
    for (auto i: in) {
        if (i.startsWith("<p>")) {
            isP = true;
        }
        if (isP) {
            tmp+=i;
        }
        if (i.endsWith("</p>")) {
            isP = false;
        }
    }
    for (auto i: tmp) {
        res = i+res;
    }
    return res;
}

QString parsing2(QStringList in) //task 2 if I got the task wrong
{
    QStringList tmp;
    QString tmp2;
    QString res;
    bool isP = false;
    for (auto i: in) {
        if (i.startsWith("<p>")) {
            isP = true;
        }
        if (isP) {
            tmp2+=i;
        }
        if (i.endsWith("</p>")) {
            tmp+= tmp2;
            tmp2 = "";
            isP = false;
        }
    }
    for (auto i: tmp) {
        res = i+res;
    }
    return res;
}


bool checkPassword(QString password){ // task 3
    bool small = false, number = false, big = false, special = false;
    if (password.size() < 6 || password.size() > 12) return false;
    for (auto i: password) {
        if (i.isDigit()) number = true;
        if (i.isLower()) small = true;
        if (i.isUpper()) big = true;
        if (i == '$' ||i == '#' ||i == '@' ||i == '!' ||i == '%' ||i == '^' || i == '&') special = true;
    }
    return small && number && big && special;
}


void printGoodPasswords(QString in) {
    QStringList passwords = in.split(", ");
    for (auto i: passwords) {

        if (checkPassword(i)) {
            qDebug() << i;
        }
    }
}

void rotate(QVector<QVector<int>>& matrix) { // transposing matrix
    int n = matrix.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            std::swap(matrix[i][j], matrix[j][i]);
        }
    }
}



int main(int argc, char *argv[])
{
    // QCoreApplication a(argc, argv);
    // qDebug() << kitNumbers(197);
    // qDebug() << kitNumbers(2021);
    // qDebug() << kitNumbers(-2);
    // qDebug() << kitNumbers(0);
    // qDebug() << kitNumbers(7385);
    // // a.exit();


    // qDebug() << parsing(htmlLines);
    // qDebug();
    // qDebug() << parsing2(htmlLines);

    printGoodPasswords(passwords);

    return 0;
}


///SQL-1

// Select name, age from Employees where status = 1 and age between 21 and 59;


///SQL-2

// select dep.name, count(*) as emp_count from
//                  (select * from Departments where status = 1) as dep
//                  inner join
//                  (Select name, age, dep_id from Employees where status = 1
// and age between 21 and 59) as emp
//                  on emp.dep_id = dep.id
//                    group by dep.name
//                    order by emp_count desc;
// ;

