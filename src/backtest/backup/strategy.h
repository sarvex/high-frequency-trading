#ifndef SRC_BACKTEST_STRATEGY_H_
#define SRC_BACKTEST_STRATEGY_H_

#include <market_snapshot.h>
#include <strategy_status.h>
#include <timecontroller.h>
#include <order.h>
#include <sender.h>
#include <exchange_info.h>
#include <order_status.h>
#include <common_tools.h>
#include <base_strategy.h>
#include <libconfig.h++>
#include <tr1/unordered_map>

#include <cmath>
#include <vector>
#include <string>


class Strategy : public BaseStrategy {
 public:
  // Strategy(std::string main_ticker, std::string hedge_ticker, int maxpos, double tick_size, TimeController tc, int contract_size, std::string strat_name, std::tr1::unordered_map<std::string, std::vector<BaseStrategy*> >*ticker_strat_map);
  Strategy(const libconfig::Setting & setting, TimeController tc, std::tr1::unordered_map<std::string, std::vector<BaseStrategy*> >*ticker_strat_map, std::string mode = "real");
  ~Strategy();

  void Start();
  void Stop();
 private:
  void DoOperationAfterUpdateData(MarketSnapshot shot);
  void DoOperationAfterUpdatePos(Order* o, ExchangeInfo info);
  void DoOperationAfterFilled(Order* o, ExchangeInfo info);
  void DoOperationAfterCancelled(Order* o);
  void ModerateOrders(std::string contract);
  void InitTicker();
  void InitTimer();
  bool Ready();
  void Pause();
  void Resume();
  void Run();
  void Train();
  void Flatting();

  double OrderPrice(std::string contract, OrderSide::Enum side, bool control_price);

  bool MidBuy();
  bool IsAlign();
  bool MidSell();


  bool IsParamOK();
  void MainLogic();
  bool HitMean();

  bool Spread_Good();

  char order_ref[MAX_ORDERREF_SIZE];
  std::string main_ticker;
  std::string hedge_ticker;
  int max_pos;
  double min_price;

  TimeController this_tc;
  int cancel_threshhold;
  std::tr1::unordered_map<std::string, double> mid_map;
  double up_diff;
  double down_diff;
  double mean;
  std::vector<double> map_vector;
  int current_pos;
  int min_profit;
  unsigned int min_train_sample;
  double min_range;
  double increment;
  std::string mode;
  double spread_threshold;
  int closed_size;
};

#endif  // SRC_BACKTEST_STRATEGY_H_
