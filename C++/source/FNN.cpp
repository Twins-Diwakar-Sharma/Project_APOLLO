#include "FNN.h"


FNN::FNN(Vec& v) : input(v)
{}

FNN::FNN(FNN& f) : layers(f.layers),
    weights(f.weights), dw(f.dw),
    biases(f.biases), db(f.db),
    input(f.input)
{
}

FNN::FNN(FNN&& f) : layers(std::move(f.layers)),
    weights(std::move(f.weights)), dw(std::move(f.dw)),
    biases(std::move(f.biases)), db(std::move(f.db)),
    input(f.input)
{
}

FNN::~FNN()
{}

FNN& FNN::operator=(FNN& f)
{
    if(&f == this)
        return *this;
    for(int i=0; i<f.layers.size(); i++)
    {
         layers.push_back(f.layers[i]);
         weights.push_back(f.weights[i]);
         dw.push_back(f.dw[i]);
         biases.push_back(f.biases[i]);
         db.push_back(f.db[i]);
         input[i] = f.input[i];
    }
   
    return *this;
}

FNN& FNN::operator=(FNN&& f)
{
    if(&f == this)
        return *this;
    layers = std::move(f.layers);
    weights = std::move(f.weights);
    dw = std::move(f.dw);
    biases = std::move(f.biases);
    db = std::move(f.db);
    input = f.input;
    return *this;
}

void FNN::push_back_WeightsAndBiases()
{
    int rows=0, cols=0;

    if(layers.size() == 0)
    {
        return;
    }
    else if(layers.size() == 1)
    {
        rows = layers.back().neurons.size();
        cols = input.size();
    }
    else 
    {
        rows = layers[layers.size()-1].neurons.size(); 
        cols = layers[layers.size()-2].neurons.size();
    }

    weights.emplace_back(rows,cols);
    randomize::normal(weights.back());
    
    dw.emplace_back(rows,cols);
    randomize::normal(dw.back());
    
    biases.emplace_back(rows);
  //  randomize::normal(biases.back());

    db.emplace_back(rows);
  //  randomize::normal(db.back());

}

void FNN::push_back_layer(Layer& l)
{
    layers.emplace_back(l.neurons.size(), l.activation);
}

void FNN::push_back_layer(Layer&& l)
{
    layers.push_back(l);
}

/*
FNN operator+(Layer& l, Layer& r)
{
    FNN f;
    f.push_back(l);
    f.push_back(r);
    f.push_back_WeightsAndBiases();
    return f;
}

FNN operator+(Layer& l, Layer&& r)
{
    FNN f;
    f.push_back(l);
    f.push_back(r);
    f.push_back_WeightsAndBiases();
    return f;
}

FNN operator+(Layer&& l, Layer& r)
{
    FNN f;
    f.push_back(l);
    f.push_back(r);
    f.push_back_WeightsAndBiases();
    return f;
}

FNN operator+(Layer&& l, Layer&& r)
{
    FNN f;
    f.push_back(l);
    f.push_back(r);
    f.push_back_WeightsAndBiases();
    return f;
}
*/

FNN operator+(FNN& f, Layer& l)
{
    FNN newF(f);
    newF.push_back_layer(l);
    newF.push_back_WeightsAndBiases();
    return newF;
}

FNN operator+(FNN& f, Layer&& l)
{
    FNN newF(f);
    newF.push_back_layer(l);
    newF.push_back_WeightsAndBiases();
    return newF;
}

FNN operator+(FNN&& f, Layer& l)
{
    f.push_back_layer(l);
    f.push_back_WeightsAndBiases();
    return f;
}

FNN operator+(FNN&& f, Layer&& l)
{
    f.push_back_layer(l);
    f.push_back_WeightsAndBiases();
    return f;
}

FNN operator+(Vec& in, Layer& l)
{
    FNN f(in);
    f.push_back_layer(l);
    f.push_back_WeightsAndBiases();
    return f;
}

FNN operator+(Vec& in, Layer&& l)
{
    FNN f(in);
    f.push_back_layer(l);
    f.push_back_WeightsAndBiases();
    return f;
}

FNN operator+(Vec& in, int i)
{
    FNN f(in);
    f.push_back_layer(i); 
    f.push_back_WeightsAndBiases();
    return f;
}

FNN operator+(FNN& f, int i)
{
    f.push_back_layer(i);
    f.push_back_WeightsAndBiases();
    return f;
}

FNN operator+(FNN&& f, int i)
{
    f.push_back_layer(i); 
    f.push_back_WeightsAndBiases();
    return f;
}


Layer operator/(int size, const Activation& a)
{
    return {size,a};
}

void FNN::forwardPass()
{
    layers[0].neurons = weights[0]*input + biases[0];
    layers[0].activate();
 //
    for(int i=1; i<layers.size(); i++)
    {
       layers[i].neurons = weights[i]*layers[i-1].neurons + biases[i]; 
 //      layers[i].neurons = weights[i]*layers[i-1].neurons; // asuming no shit in multiply
       layers[i].activate();
    }

}

void FNN::backwardPass()
{
    
   for(int w=weights.size()-1; w>=0; w--)
   {
        for(int j=0; j<weights[w].col(); j++)
        {
            if(w>0)
                layers[w-1].error[j] = 0;
            for(int k=0; k<weights[w].row(); k++)
            {
              //  printf("w[%d][%d][%d]\n",w,j,k);
                float temp = layers[w].error[k] * layers[w].deactivate(k);
                if(w>0)     [[likely]]
                {
                   layers[w-1].error[j] += temp * weights[w][k][j];
                   dw[w][k][j] = temp * layers[w-1].neurons[j];
                }
                else    [[unlikely]]
                {
                    dw[w][k][j] = temp * input[j];
                }
           }
        }

        for(int k=0; k<weights[w].row(); k++)
        {
            db[w][k] = layers[w].error[k] * layers[w].deactivate(k);
        }    
   }

//    for(int w=weights.size()-1; w>0; w--)
//    {
//        for(int r=0; )   
//    }
  
}

void FNN::gradientDescend()
{
    for(int w=0; w<weights.size(); w++)
    {
        weights[w] += -alpha * dw[w];
    }

    for(int b=0; b<biases.size(); b++)
    {
        biases[b] += -alpha * db[b];
    }
}

void FNN::train(int epoch, std::string imagePath, std::string labelPath)
{
   
  std::ifstream images;
  std::ifstream labels;

  int magicNo,totalImages,row,col,totalLabels;

  int outputSize = layers.back().neurons.size();

  Vec target(outputSize); 
   
  while(epoch--)
  {
      images.open(imagePath);
      labels.open(labelPath);
      dataset.getConfig(images,magicNo,totalImages,row,col);
      dataset.getLabelConfig(labels,magicNo,totalLabels);

      int imagesLeft = totalImages;
      while(imagesLeft--)
      {
          if(imagesLeft%1000 == 0)
          {
              std::cout << totalImages - imagesLeft << std::endl;
          }
      
          int targetIndex = dataset.getNextDatasetLabel(labels);
          target.reset();
          target[targetIndex] = 1;

          input = dataset.getNextDatasetImage(images,row,col);
            
          forwardPass(); 
          
          for(int i=0; i<target.size(); i++)
          {
             layers.back().error[i] = -2*(target[i]-layers.back().neurons[i]); 
          }
            
          backwardPass();

          gradientDescend();
      }
      images.close();
      labels.close();

  }

}

void FNN::test(std::string imagePath, std::string labelPath)
{
   
  std::ifstream images;
  std::ifstream labels;

  int magicNo,totalImages,row,col,totalLabels;

  int outputSize = layers.back().neurons.size();

  Vec target(outputSize); 

   
  images.open(imagePath);
  labels.open(labelPath);
  dataset.getConfig(images,magicNo,totalImages,row,col);
  dataset.getLabelConfig(labels,magicNo,totalLabels);

  int imagesLeft = totalImages;


  //todo soft code this hardcoded 10
  float errorPerNumber[10];
  int count[10];
  float avgError = 0;

  for(int i=0; i<10; i++)
  {
      errorPerNumber[i] = 0;
      count[i] = 0;
  }

    int noLines=0;
    imagesLeft = 50;
  while(imagesLeft--)
  {
      if(imagesLeft%1000 == 0)
      {
          std::cout << totalImages - imagesLeft << std::endl;
      }
  
      int targetIndex = dataset.getNextDatasetLabel(labels);
      target.reset();
      target[targetIndex] = 1;

      input = dataset.getNextDatasetImage(images,row,col);
/*        for(int r=0; r<28; r++)
      {
        for(int c=0; c<28; c++)
        {
            float value = input[r*28 + c];
            if(value > 0.6f)
                std::cout << "X ";
            else
                std::cout << ". ";
        }
        std::cout << std::endl;
      }

*/
      forwardPass(); 
        

        
      float error=0;
      std::cout << targetIndex << " : ";
      std::cout << layers.back().neurons << " \n" << std::endl;

      for(int i=0; i<target.size(); i++)
      {
         float t = (target[i]-layers.back().neurons[i]); 
         error += t*t;
      }

      error = sqrt(error);
       
      errorPerNumber[targetIndex] += error;
      count[targetIndex]++;

      avgError += error;
      noLines++;
  }
  images.close();
  labels.close();

  avgError = avgError/noLines;

  std::cout << "----------------***----------------\navgError : " << avgError << std::endl;
  std::cout << " error per number " << std::endl;
  for(int i=0; i<10; i++)
  {
      std::cout << i << " : " << errorPerNumber[i]/count[i] << std::endl;
  }


}


