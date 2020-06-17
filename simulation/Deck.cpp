#include "../simulation/Deck.h"

#include <algorithm>
#include <stdexcept>

#include <iostream>
#include "../utils/Hoy.h"
#include "../utils/Hoy2.h"
#include "../utils/Sort.h"

Deck::Deck(){
    
}

Deck::Deck(std::vector<double> values, int n, int m, std::vector<double> min, std::vector<double> max){
    this->n = n;
    this->m = m;
    this->cards = std::vector<Card>(n);
    for(int i=0; i<n*m; i+=m){
        cards[i/m] = Card(values, m, i);
    }
    this->computeRanks();
    this->min = min;
    this->max = max;
}

Deck::Deck(int n, int m, double min, double max, int seed){
    std::default_random_engine re(seed);
    this->n = n;
    this->m = m;
    this->min = std::vector<double>(this->m, min);
    this->max = std::vector<double>(this->m, max);
    this->cards = std::vector<Card>(n);
    std::uniform_real_distribution<double> unif(min, max);
    for(int i=0; i<n; i++){
        std::vector<double> card_values(m);
        for(int j=0; j<m; j++){
            card_values[j] = unif(re);
        }
        cards[i] = Card(card_values, m,0);
    }
    this->computeRanks();
}

void Deck::computeRanks(){
    for(int i=0; i<this->m; i++){
        std::vector<double> colValues(this->n);
        std::vector<size_t> idx;
        std::vector<double> b;
        for(int j=0; j<this->n; j++){
            colValues[j] = this->cards[j].getValue(i);
        }
        sort(colValues, b, idx);
        for(int j=0; j<this->n; j++){
            this->cards[(int)idx[j]].setRank(j, i);
        }
    }

}

void Deck::shuffle(){
    std::random_shuffle(&cards[0], &cards[n]);
}

std::vector<std::vector<Card>> Deck::distribute(int players){
    if(n%players !=0){
        throw std::invalid_argument("deck can not be divided to players");
    }
    int hand = n/players;
    std::vector<std::vector<Card>> distribution(players);
    int counter = 0;
    for(int i=0; i<players; i++){
        distribution[i] = std::vector<Card>(hand);
        for(int j=0; j<hand; j++){
            distribution[i][j] = cards[counter];
            counter++;
        }
    }
    return distribution;
}

std::vector<Card> Deck::getCards(){
    return this->cards;
}

int Deck::getM(){
    return this->m;
}

int Deck::getN(){
    return this->n;
}

/* Hypervolume computation using the code from Hoy.cpp */
double Deck::getHV(){
    std::vector<double> refPoint = this->max;
    std::vector<double>values(this->n*this->m);
    int counter =0;
    for(int i =0; i<this->n; i++){
        Card card = this->cards[i];
        for(int j=0; j<this->m; j++){
            values[counter] = card.getValue(j);
            counter++;
        }
    }
    for(int i=0; i<this->m; i++){
        refPoint[i]+=1;
    }
    HVCalculator hv;
    //int dimension, int dataNumber, double* points, double* refPoint
    return hv.computeHV(this->m, this->n, values, refPoint);;
}

/* Hypervolume computation using the code from Hoy2.cpp */
double Deck::getHV2(){
    std::vector<double>refPoint = this->max;
    std::vector<std::vector<double>> values;
    for(int i =0; i<this->n; i++){
        Card card = this->cards[i];
        std::vector<double> v(this->m);
        for(int j=0; j<this->m; j++){
          v[j] = card.getValue(j);
        }
        values.push_back(v);
    }
    for(int i=0; i<this->m; i++){
        refPoint[i]+=1;
    }
    Hoy hv;
    return hv.compute(values, refPoint);;
}

double Deck::getSD(){
    std::vector<double> colSums(this->m, 0);
    double mean=0;
    for(int i=0; i<this->n; i++){
        Card card = this->cards[i];
        for(int j=0; j<this->m; j++){
            colSums[j] += card.getValue(j)/this->n;
            mean +=card.getValue(j)/this->n;
        }
    }
    mean/=this->m;
    double sd = 0;
    for(int i=0; i<this->m; i++){
        sd+=(colSums[i] - mean)*(colSums[i] -mean);
    }
    sd/=(this->m-1);
    sd = std::sqrt(sd);
    return(sd);
}


std::vector<double> Deck::getMin(){
    return this->min;
}

std::vector<double> Deck::getMax(){
    return this->max;
}
