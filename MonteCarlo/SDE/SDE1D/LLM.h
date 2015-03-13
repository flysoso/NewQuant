#ifndef LLM_H
#define LLM_H

namespace NewQuant
{

    
    class LLM
    {
    protected:
        double drift_;
        double diffusion_;
        LLM() {}
    public:
        virtual double operator () (const double &x) const = 0;
        ~LLM(){}
    };

    
    class LLMdrift : public LLM
    {
    public :
        LLMdrift(){}
        double operator () (const double &x) const
        {return 5.0 - 11.0*x + 6.0*x*x - x*x*x;}
        ~LLMdrift(){}
    };

    
    class LLMdiffusion : public LLM
    {
    public :
        LLMdiffusion(){}
        double operator () (const double &x) const {return 1.0;}
        ~LLMdiffusion(){}
    };

    
    class LLMdrift_x : public LLM
    {
    public :
        LLMdrift_x(){}
        double operator () (const double &x) const
        {return -11.0 + 12.0*x - 3.0*x*x;}
        ~LLMdrift_x(){}
    };

    
    class LLMdiffusion_x : public LLM
    {
    public :
        LLMdiffusion_x(){}
        double operator () (const double &x) const {return 0.0;}
        ~LLMdiffusion_x(){}
    };

    
    class LLMdrift_xx : public LLM
    {
    public :
        LLMdrift_xx(){}
        double operator () (const double &x) const
        {return 12.0 - 6.0*x;}
        ~LLMdrift_xx(){}
    };

    
    class LLMdiffusion_xx : public LLM
    {
    public :
        LLMdiffusion_xx(){}
        double operator () (const double &x) const {return 0.0;}
        ~LLMdiffusion_xx(){}
    };
}





#endif//LLM_H

