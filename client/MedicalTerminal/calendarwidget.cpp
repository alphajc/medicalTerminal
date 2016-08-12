#include "calendarwidget.h"

CalendarWidget::CalendarWidget()
{
    Init();
    setTodayFont();
}

QString CalendarWidget::getTraditionMD(QDate nowDay)
{
    int currentYear = 0, currentMonth = 0, currentDay = 0;
    int nTheDate = 0, nTheMonth = 0;
    int nisEnd = 0, flag = 0, n = 0, k = 0, nBit = 0, i = 0;
    char m_LunarMD[100] = {0}, m_LunarYear[50] = {0}, m_LunarMonth[50] = {0}, m_LunarDay[50] = {0}, m_zodiak[50] = {0};
    /*天干名称*/
    const char *m_TianGan[] = {"甲","乙","丙","丁","戊","己","庚","辛","壬","癸"};
    /*地支名称*/
    const char *m_DiZhi[] = {"子","丑","寅","卯","辰","巳","午","未","申","酉","戌","亥"};
    /*属相名称*/
    const char *m_ShuXiang[] = {"鼠","牛","虎","兔","龙","蛇","马","羊","猴","鸡","狗","猪"};
    /*农历日期名*/
    const char *m_DayName[] = {"*","初一","初二","初三","初四","初五",
          "初六","初七","初八","初九","初十",
          "十一","十二","十三","十四","十五",
          "十六","十七","十八","十九","二十",
          "廿一","廿二","廿三","廿四","廿五",
          "廿六","廿七","廿八","廿九","三十"};
     /*农历月份名*/
    const char *m_MonthName[] = {"*","正","二","三","四","五","六","七","八","九","十","十一","腊"};
    /*公历每月前面的天数*/
    const int m_DayAdd[12] = {0,31,59,90,120,151,181,212,243,273,304,334};
    /*农历数据*/
    const int m_LunarData[100]= {2635,333387,1701,1748,267701,694,2391,133423,1175,396438
                                 ,3402,3749,331177,1453,694,201326,2350,465197,3221,3402
                                 ,400202,2901,1386,267611,605,2349,137515,2709,464533,1738
                                 ,2901,330421,1242,2651,199255,1323,529706,3733,1706,398762
                                 ,2741,1206,267438,2647,1318,204070,3477,461653,1386,2413
                                 ,330077,1197,2637,268877,3365,531109,2900,2922,398042,2395
                                 ,1179,267415,2635,661067,1701,1748,398772,2742,2391,330031
                                 ,1175,1611,200010,3749,527717,1452,2742,332397,2350,3222
                                 ,268949,3402,3493,133973,1386,464219,605,2349,334123,2709
                                 ,2890,267946,2773,592565,1210,2651,395863,1323,2707,265877};

    currentYear = nowDay.year();
    currentMonth = nowDay.month();
    currentDay = nowDay.day();
    nTheMonth = (currentYear- 1921) * 12 - 2 + currentMonth;

    sprintf(m_LunarMonth, "%s%s月", m_TianGan[(nTheMonth + 6) % 10], m_DiZhi[(nTheMonth + 2) % 12]);

    /*---计算到初始时间1921年2月8日的天数：1921-2-8(正月初一)---*/
    nTheDate = (currentYear - 1921) *365 + (currentYear - 1921)/4  + m_DayAdd[currentMonth - 1] + currentDay - 31 - 7;
    if((!(currentYear % 4)) && (currentMonth > 2))
        nTheDate = nTheDate + 1;

    sprintf(m_LunarDay, "%s%s日", m_TianGan[(nTheDate + 7) % 10], m_DiZhi[(nTheDate + 1) % 12]);

    /*--计算农历天干、地支、月、日---*/
    nisEnd = 0;
    flag = 0;
    while (nisEnd != 1) {
        if (m_LunarData[flag] < 4095)  k = 11;
        else  k = 12;
        n = k;
        while (n >= 0) {
             //m_LunarData(flag)的第n个二进制位的值
            nBit = m_LunarData[flag];
            for (i = 1; i < n + 1; i++)  nBit = nBit / 2;
            nBit = nBit % 2;
            if (nTheDate <= (29 + nBit)) {
                nisEnd = 1;
                break;
            }
            nTheDate = nTheDate - 29 - nBit;
            n = n - 1;
        }
        if (nisEnd)  break;
        flag = flag + 1;
    }
    currentYear = 1921 + flag;
    currentMonth = k - n + 1;
    currentDay = nTheDate;
    if (k == 12) {
        if (currentMonth == m_LunarData[flag] / 65536 + 1)  currentMonth = 1 - currentMonth;
        else if (currentMonth > m_LunarData[flag] / 65536 + 1)  currentMonth = currentMonth - 1;
    }
    /*--生成农历天干、地支、属相*/
    sprintf(m_zodiak, "%s", m_ShuXiang[((currentYear - 4) % 60) % 12]);
    sprintf(m_LunarYear, "%s%s年 【%s年】", m_TianGan[((currentYear - 4) % 60) % 10], m_DiZhi[((currentYear - 4) % 60) % 12], m_zodiak);
    /*--生成农历月、日*/
    if (currentMonth < 1)
        sprintf(m_LunarMD ,"闰%s", m_MonthName[-1 * currentMonth]);
    else
        strcpy(m_LunarMD, m_MonthName[currentMonth]);
    strcat(m_LunarMD,"月");
    strcat(m_LunarMD, m_DayName[currentDay]);

    return tr(m_LunarMD);
//    outLunarYear = tr(m_LunarYear);
//    outLunarMonth = tr(m_LunarMonth);
//    outLunarDay = tr(m_LunarDay);
}

void CalendarWidget::timeLook()
{
    date = calendar->selectedDate();
    timeLabel->setText(date.toString("yyyy-MM-dd dddd"));

    traditionalTimeLabel->setText(getTraditionMD(date));
}

void CalendarWidget::todayLook()
{
    calendar->setSelectedDate(m_Today);
}



void CalendarWidget::Init()
{
    setWindowFlags(Qt::FramelessWindowHint);

    calendar = new QCalendarWidget(this);
    calendar->setMinimumDate(QDate(1900, 1, 1));
    calendar->setMaximumDate(QDate(3000, 1, 1));
    calendar->setGridVisible(true);
    calendar->setGeometry(0,20,240,280);
    calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

    timeLabel = new QLabel(this);
    date = calendar->selectedDate();
    m_Today = QDate(calendar->selectedDate());
    timeLabel->setStyleSheet("font-size:14px; color: #008080;");
    timeLabel->setText(date.toString("yyyy-MM-dd dddd"));
    timeLabel->setGeometry(120,300,120,20);

    traditionalTimeLabel = new QLabel(this);
    traditionalTimeLabel->setStyleSheet("font-size:20px; color:#800080; font:bold;");
    traditionalTimeLabel->setText(getTraditionMD(calendar->selectedDate()));
    traditionalTimeLabel->setGeometry(0,300,100,20);

    connect(calendar,SIGNAL(selectionChanged()),this,SLOT(timeLook()));

    todayButton = new QPushButton(this);
    todayButton->setText(tr("当前日期"));
    todayButton->setGeometry(10,0,80,20);
    connect(todayButton,SIGNAL(clicked()),this,SLOT(todayLook()));

    returnButton = new QPushButton(this);
    returnButton->setIcon(QIcon(":/img/PLayer_back_24px_1184881_easyicon.net.png"));
    returnButton->setFlat(true);
    returnButton->setToolTip(tr("返回"));
    returnButton->setGeometry(215,0,20,20);
    connect(returnButton,SIGNAL(clicked()),this,SLOT(hide()));

    setWindowTitle(tr("日历"));
    setFixedSize(240, 320);

}

void CalendarWidget::setTodayFont()
{
    QDate tdate=QDate::currentDate();
    QTextCharFormat todayFormat;
    todayFormat.setBackground(Qt::yellow);
    todayFormat.setFontPointSize(13);
    todayFormat.setFontWeight(17);
    todayFormat.setFontUnderline(true);
    calendar->setDateTextFormat(tdate,todayFormat);
}
