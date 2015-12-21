#include "antcolonyalgorithmprocessor.h"

antColonyAlgorithmProcessor::antColonyAlgorithmProcessor(): MethodProcessor()
{
    m_iterations = 500;
    m_vaporization = 0.5;
    m_greed = 0.9;
    m_herdy = 0.1;
}

void antColonyAlgorithmProcessor::start(QList<City> points){

    int size = points.size();
    int iter=m_iterations;

    //парамтеры алгоритма
    double jad = m_greed;
    double stad = m_herdy;
    double isp= m_vaporization;
    double** arr = new double*[size];//матрица переходов
    for(int i=0;i<size;i++){
        arr[i]= new double[size];
        for(int j=0;j<size;j++)
            arr[i][j]=estimatePoints(points[i],points[j]);
    }
    double** ferom = new double*[size]; // матрица феромонов на путях
    for(int i=0;i<size;i++)
        ferom[i]= new double[size];
    QList<int> mur [points.size()];      // массивы муравьев с уже пройденными путями на путях
    double mur_dl [size];// массивы длин путей муравьев
    double GlpBestSol = qInf();
    QList<int> GlpBestWay;
    QList<int> GlpTempWay;
    for (int i = 0; i < size; i++) // заполнение феромонов
    {
        for (int j = 0; j < size; j++)
        {
            ferom[i][j] = 0.9; //начальное кол-во феромона
        }
    }
    int l = 0;
    while (l < iter)
    {
        for (int i = 0; i < size; i++) // заполнение матрицы муравьев
        {
            mur[i] = QList<int>();
            mur[i].append(i);
            mur_dl[i] = 0;
        }
        l++;
        while (mur[size - 1].size() != size) // пока муравьи не сделали полный цикл
        {
            for (int i = 0; i < size; i++) // цикл по всем муравьям
            {
                QList<double> P; // список вероятностей переходов в города
                QList<int> Pnumbers; // список городов для которых считаем вероятности
                for (int j = 0; j < size; j++) // цикл по городам
                {
                    if (mur[i].contains(j)) // если город уже есть в пути муравья
                    {
                        continue;
                    }
                    else // считаем вероятность перехода в город, записываем город в список возможных
                    {
                        P.append(qPow((1 / arr[mur[i].at(mur[i].size() - 1)][ j]), jad)
                            * qPow(ferom[mur[i].at(mur[i].size() - 1)][ j], stad));
                        Pnumbers.append(j);
                    }
                }
                int next = Pnumbers.at(Pnumbers.size() - 1); // по умолчанию он пойдет в последний город
                double sum = 0;
                for(int ii=0;ii<P.size();ii++)
                    sum += P[ii];
                for (int k = 0; k < P.size(); k++)
                { P[k] = P.at(k) / sum; } // нормализуем вероятности перехода
                // генерируем случайное число от 0 до 1
                double temp;
                temp = double(qrand()%101) / 100;
                double balda = 0;
                for (int k = 0; k < P.size(); k++) // смотрим в какой город он пойдет
                {
                    balda += P.at(k);
                    if (temp <= balda)
                    {
                        next = Pnumbers.at(k);
                        break;
                    }
                }
                mur_dl[i] += arr[mur[i].at(mur[i].size() - 1)][ next];
                mur[i].append(next); // добавляем город в путь
            }
            for (int i = 0; i < size; i++) // испарение феромонов
            {
                for (int j = 0; j < size; j++)
                {
                    ferom[i][ j] = (1 - isp) * ferom[i][ j];
                }
            }
            for (int i = 0; i < size; i++) // добавление феромонов
            {
                ferom[mur[i].at(mur[i].size() - 2)][ mur[i].at(mur[i].size() - 1)] += mur[i].size() / mur_dl[i];
            }
        }
        for (int i = 0; i < size; i++) // выбираем лучший путь
        {
            mur_dl[i] += arr[mur[i].at(mur[i].size() - 1)][ mur[i].at(0)];
            if (mur_dl[i] < GlpBestSol)
            {
                GlpBestSol = mur_dl[i];
                GlpBestWay = mur[i];
                Cities result;
                for(int i=0;i<GlpBestWay.size();i++)
                    result.append(points[GlpBestWay[i]]);
                emit(newBestFound(result));
            }
        }
    }
    Cities result;
    for(int i=0;i<GlpBestWay.size();i++)
        result.append(points[GlpBestWay[i]]);
    emit(done(result));
}



bool antColonyAlgorithmProcessor::setIterations(int iterations){
    if (iterations>0){
        m_iterations=iterations;
        return true;
    }
    return false;
}

bool antColonyAlgorithmProcessor::setGreed(double greed){
    if (greed>=0 && greed<=1){
        m_greed = greed;
        return true;
    }
    return false;
}

bool antColonyAlgorithmProcessor::setHerdy(double herdy){
    if (herdy>=0 && herdy<=1){
        m_herdy = herdy;
        return true;
    }
    return false;
}

bool antColonyAlgorithmProcessor::setVaporization(double vaporization){
    if (vaporization>=0 && vaporization<=1){
        m_vaporization = vaporization;
        return true;
    }
    return false;
}
