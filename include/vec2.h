#ifndef _VEC2_H_
#define _VEC2_H_

#include <cmath>


template <class T>
class vec2 {
    public:

        
        T x, y; 
        vec2() :x(0), y(0){}
        vec2(T x, T y) : x(x), y(y) {}
        vec2 (const vec2& v) : x( v.x), y( v.y){}


        vec2& operator= (const vec2& v){
            x = v.x;
            y = v.y;
            return *this;
        }

        vec2 operator+ (const vec2& v){
            return vec2( x + v.x, y + v.y);
        }

        vec2 operator- (const vec2& v){
            return vec2(x - v.x, y - v.y);
        }


        vec2 operator+ ( double d){
            return vec2(x + d, y + d);
        }

        vec2 operator- ( double d){
            return vec2 (x - d, y - d);
        }

        vec2 operator* (double d){
            return vec2(x * d , y * d);
        }

        vec2 operator/ (double d){
            return vec2(x * d, y * d);
        }


        bool operator== ( const vec2& v){
            if ((this -> x == v.x) && (this -> y == v.y)) {
                return true;
            }
            else{
                return false;
            }
        }

        vec2& operator+= (double d ){
            x += d;
            y += d; 
            return *this; 
        }

        vec2& operator-= (double d ){
            x -= d;
            y -= d; 
            return *this;
        }
        
        vec2& operator*= (double d){
            x *= d;
            y *= d;
            return *this;
        }
        vec2& operator/= (double d ){
            x /= d; 
            y /= d;
            return *this; 
        }

        /**
         * @brief Sets the values for the vec2
         * 
         * @param x x-position  
         * @param y y-position
         */
        void set( T x, T y){
            this -> x = x;
            this -> y = y;
        }

        /**
         * @brief distance of the vec2 to another using euclidean distance.
         * 
         * @param v 2nd vector
         * @return float distance between the two vec2 
         */
        float dist (vec2 v) const {
            return std::sqrt ( std::pow((this -> x - x), 2.0 )+ std::pow((this -> y - y), 2.0 ) );
        }
};

typedef vec2 <double> vec2d;
typedef vec2<float> vec2f;

#endif /* _VEC2D_H_ */
