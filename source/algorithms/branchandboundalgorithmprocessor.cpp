#include "branchandboundalgorithmprocessor.h"




BranchAndBoundAlgorithmProcessor::BranchAndBoundAlgorithmProcessor()
{

}


void BranchAndBoundAlgorithmProcessor::start(QList<City> points){
    m_points = points;

    double** fr_array = new double*[points.size() + 1];
    for(int i=0;i<points.size();i++)
        fr_array[i] = new double[points.size() + 1];
    int arr_razm = points.size();
    GltBestSol = 10000;
    QList<int> way ;
    for (int i = 0; i < arr_razm; i++)
    {
        for (int j = 0; j < arr_razm; j++)
        { fr_array[i][j] = estimatePoints(points[i],points[j]); }
    }
    GltBestSol = 10000; //?  второй раз записываем 10к?
    double v = ves(fr_array, arr_razm, way);
    front(fr_array, arr_razm, way);

    Cities result;
    for(int i=0;i<GltBestWay.size();i++)
        result.append(points[GltBestWay[i]]);
    emit(newBestFound(result));
    emit(done(result));
}

Cities BranchAndBoundAlgorithmProcessor::B(int i, QList<int> M){
    if (Bs.contains(BPar(i,M))){
        //вернем существующее решенеие
        return Bs[BPar(i,M)];
    }
    if (M.size()>1){
        int minRes = qInf();
        Cities minRoute;
        QList<Cities> results;
        for(int ii=0;ii<M.size();ii++){
            QList<int> Mreduced = M;
            Mreduced.removeAt(ii);
            Cities route;
            route.push_back(m_points[i]);
            Cities smallRoute= B(M[ii],Mreduced);
            for(int k=0;k<smallRoute.size();k++)
                route.push_back(smallRoute[k]);
            results.append(route);
        }
        for (int j=0;j<results.size();j++)
            if(minRes > estimate(results[j])){
                minRoute = results[j];
                minRes = estimate(results[j]);
            }
        Bs[BPar(i,M)] = minRoute;
        return minRoute;
    }
    else{
        Cities res;
        res.append(m_points[i]);
        res.append(m_points[M[0]]);
        res.append(m_points[0]);
        Bs[BPar(i,M)] = res;
        return res;
    }
}

// Фронтальное ветвление рекурсивная функция
double BranchAndBoundAlgorithmProcessor::front(double** fr_array, int size,  QList<int> way){
    QList<int> wayNum;
    QList<double> waySol;

    double tempV;
    for (int i = 0; i < size; i++)
    {
        if (way.contains(i))
            continue;
        else
        {
            way.append(i);
            tempV = ves(fr_array, size, way);
            if (way.count() == size)
            {
                GltTempWay = way;
                way.removeOne(i);
                return tempV;
            }
            int flag = 0;
            for (int k = 0; k < waySol.count(); k++)
            {
                if (waySol.at(k) > tempV)
                {
                    waySol.insert(k, tempV);
                    wayNum.insert(k, i);
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                waySol.append(tempV);
                wayNum.append(i);
            }
            way.removeOne(i);
        }
    }

    for (int k = 0; k < wayNum.count(); k++)
    {
        if (GltBestSol > waySol.at(k))
        {
            way.append(wayNum.at(k));
            tempV = front(fr_array,size, way);
            if (tempV < GltBestSol)
            {
                GltBestSol = tempV;
                GltBestWay = GltTempWay;
                Cities newBest;
                for(int i=0;i<GltTempWay.size();i++)
                    newBest.append(m_points[GltTempWay[i]]);
                emit(newBestFound(newBest));
            }
            way.removeAt(wayNum.at(k));
        }
    }
    return GltBestSol;
}

double BranchAndBoundAlgorithmProcessor::ves(double** array, int size, QList<int> lok_way){
    double lok_v = 0;
    int arr_razm = size;
    double** fr_lok_array = new double*[size + 1];
    for(int i=0;i<(size+1);i++)
        fr_lok_array[i] = new double[size+1];
    for (int i = 0; i < arr_razm; i++)
    {
        for (int j = 0; j < arr_razm; j++)
        { fr_lok_array[i][j] = array[i][j]; }
    }
    if (lok_way.count()> 1)
    {
        for (int k = 0; k < lok_way.count()-1; k++)
        {
            double el = fr_lok_array[lok_way.at(k)][ lok_way.at(k+1)];
            for (int i = 0; i < arr_razm; i++)
            {
                for (int j = 0; j < arr_razm; j++)
                {
                    fr_lok_array[i][ lok_way.at(k+1)] = -1;
                    fr_lok_array[lok_way.at(k)][ j] = -1;
                }
            }
            fr_lok_array[lok_way.at(k)][ lok_way.at(k+1)] = el;
        }
    }
    for (int j = 0; j < arr_razm; j++) //записываем что-нибудь в мин. пути столбцов
    {
        fr_lok_array[arr_razm][ j] = 10000;
    }
    for (int i = 0; i < arr_razm; i++)
    {
        fr_lok_array[i][ arr_razm] = 10000; //записываем что-нибудь в мин. пути строк
        for (int j = 0; j < arr_razm; j++) //записываем мин. пути строк
        {
            if (fr_lok_array[i][ arr_razm] > fr_lok_array[i][ j] && fr_lok_array[i][ j] >= 0)
                fr_lok_array[i][ arr_razm] = fr_lok_array[i][ j];
        }
        for (int j = 0; j < arr_razm; j++) //вычитаем по строкам мин. пути по стокам
        {
            fr_lok_array[i][ j] -= fr_lok_array[i][ arr_razm];
        }
    }
    for (int j = 0; j < arr_razm; j++)
    {
        for (int i = 0; i < arr_razm; i++)
        {
            if (fr_lok_array[arr_razm][ j] > fr_lok_array[i][ j] && fr_lok_array[i][ j] >= 0) //записываем мин. пути столбцов
                fr_lok_array[arr_razm][ j] = fr_lok_array[i][ j];
        }
        for (int i = 0; i < arr_razm; i++) //вычитаем по строкам мин. пути по столбцам
        {
            fr_lok_array[i][ j] -= fr_lok_array[arr_razm][ j];
        }
    }
    for (int i = 0; i < arr_razm; i++)
    {
        lok_v += fr_lok_array[i][ arr_razm];
        lok_v += fr_lok_array[arr_razm][ i];
    }
    for (int i = 0; i < (arr_razm+1); i++)
    {
        delete[] fr_lok_array[i];
    }
    delete[] fr_lok_array;
    return lok_v;
}
