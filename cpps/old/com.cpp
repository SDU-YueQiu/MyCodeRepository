#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>

using namespace std;
const int MAXN = 1000;

void solve(int type)
{
    if (type == 1)
    {
        printf("\n输入数据组数：");
        int nf;
        cin >> nf;

        printf("\n输入数据（以空格隔开）：");
        double f[MAXN];
        for (int i = 0; i < nf; i++)
            cin >> f[i];
        double sum = 0;
        for (int i = 0; i < nf; i++)
            sum += f[i];
        double fp = sum / nf;
        printf("\n输入△f：");
        double df;
        cin >> df;
        double Usf = 0;
        for (int i = 0; i < nf; i++)
            Usf += (f[i] - fp) * (f[i] - fp) / ((nf - 1) * nf);
        Usf += (df / sqrt(3.0)) * (df / sqrt(3.0));
        Usf = sqrt(Usf);
        printf("\n平均f= %f kHz", fp);
        printf("\n标准不确定度Usf= %f ", Usf);

        int nL;
        printf("\n输入数据组数：");
        cin >> nL;
        double L[MAXN];
        printf("\n输入数据Li（以空格隔开）：");
        for (int i = 0; i < nL; i++)
            cin >> L[i];
        double L8[MAXN];
        printf("\n输入数据Li+8（以空格隔开）：");
        for (int i = 0; i < nL; i++)
            cin >> L8[i];
        double lamd = 0;
        for (int i = 0; i < nL; i++)
            lamd += 2 * (L8[i] - L[i]) / (8 * 8);
        printf("\n输入△λ：");
        double dlamd;
        cin >> dlamd;
        double UsL = 0;
        for (int i = 0; i < nL; i++)
            UsL += (0.25 * (L8[i] - L[i]) - lamd) * (0.25 * (L8[i] - L[i]) - lamd) / ((nL - 1) * nL);
        UsL += (dlamd / sqrt(3.0)) * (dlamd / sqrt(3.0));
        UsL = sqrt(UsL);
        printf("\n平均λ= %f cm", lamd);
        printf("\n标准不确定度为UsL= %f ", UsL);

        printf("\n计算结果v= %f m/s", fp * 10 * lamd);
        double v = fp * 10 * lamd;
        double v0 = 340.0;
        double cha = abs(v - v0) / v0 * 100;
        printf("\n计算结果与标准值340m/s的误差为%f%%", cha);
        double Usv = v * sqrt((Usf / fp) * (Usf / fp) + (UsL / lamd) * (UsL / lamd));
        printf("\n标准不确定度为Usv= %f ", Usv);
    }
    if (type == 2)
    {
        printf("\n输入数据组数：");
        int nf;
        cin >> nf;

        printf("\n输入数据（以空格隔开）：");
        double f[MAXN];
        for (int i = 0; i < nf; i++)
            cin >> f[i];
        double sum = 0;
        for (int i = 0; i < nf; i++)
            sum += f[i];
        double fp = sum / nf;
        printf("\n输入△f：");
        double df;
        cin >> df;
        double Usf = 0;
        for (int i = 0; i < nf; i++)
            Usf += (f[i] - fp) * (f[i] - fp) / ((nf - 1) * nf);
        Usf += (df / sqrt(3.0)) * (df / sqrt(3.0));
        Usf = sqrt(Usf);
        printf("\n平均f= %f kHz", fp);
        printf("\n标准不确定度为Usf= %f ", Usf);

        int nL;
        printf("\n输入数据组数：");
        cin >> nL;
        double L[MAXN];
        printf("\n输入数据Li（以空格隔开）：");
        for (int i = 0; i < nL; i++)
            cin >> L[i];
        double L8[MAXN];
        printf("\n输入数据Li+8（以空格隔开）：");
        for (int i = 0; i < nL; i++)
            cin >> L8[i];
        double lamd = 0;
        for (int i = 0; i < nL; i++)
            lamd += (L8[i] - L[i]) / (8 * 8);
        printf("\n输入△λ：");
        double dlamd;
        cin >> dlamd;
        double UsL = 0;
        for (int i = 0; i < nL; i++)
            UsL += (0.125 * (L8[i] - L[i]) - lamd) * (0.125 * (L8[i] - L[i]) - lamd) / ((nL - 1) * nL);
        UsL += (dlamd / sqrt(3.0)) * (dlamd / sqrt(3.0));
        UsL = sqrt(UsL);
        printf("\n平均λ= %f cm", lamd);
        printf("\n标准不确定度为UsL= %f ", UsL);

        printf("\n计算结果v= %f m/s", fp * 10 * lamd);
        double v = fp * 10 * lamd;
        double v0 = 340.0;
        double cha = abs(v - v0) / v0 * 100;
        printf("\n计算结果与标准值340m/s的误差为%f%%", cha);
        double Usv = v * sqrt((Usf / fp) * (Usf / fp) + (UsL / lamd) * (UsL / lamd));
        printf("\n标准不确定度为Usv= %f ", Usv);
    }
    if (type == 3)
    {
        int nl;
        printf("数据组数为：6");
        nl = 6;
        double L[MAXN];
        printf("\n输入数据Li（以空格隔开）：");
        for (int i = 0; i < nl; i++)
            cin >> L[i];
        printf("\n输入数据ti（以空格隔开）：");
        double t[MAXN];
        for (int i = 0; i < nl; i++)
            cin >> t[i];
        double v = 0;
        for (int i = 0; i < 3; i++)
            v += (L[i + 3] - L[i]) / (t[i + 3] - t[i]) / 3.0;
        v *= 1e4;
        printf("\n输入标准声速：");
        double v0;
        cin >> v0;
        printf("\n计算结果v= %f m/s", v);
        double cha = abs(v - v0) / v0 * 100;
        printf("\n计算结果与标准值340m/s的误差为%f%%", cha);
    }
    return;
}

int main()
{
    int type;
    printf("输入实验方法:\n1-驻波法\n2-相位比较法\n3-时差法\n");
    cin >> type;
    double v;
    solve(type);
    return 0;
}