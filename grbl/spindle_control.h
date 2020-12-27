/*
  spindle_control.h - spindle control methods
  Part of Grbl

  Copyright (c) 2012-2016 Sungeun K. Jeon for Gnea Research LLC
  Copyright (c) 2009-2011 Simen Svale Skogsrud

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef spindle_control_h
#define spindle_control_h

#define SPINDLE_NO_SYNC false
#define SPINDLE_FORCE_SYNC true

#define SPINDLE_STATE_DISABLE  0  // Must be zero.
#define SPINDLE_STATE_CW       bit(0)
#define SPINDLE_STATE_CCW      bit(1)

#ifdef VARIABLE_SPINDLE

  #ifdef STM32
    #define SPINDLE_PWM_TYPE    uint16_t
  #else
    #define SPINDLE_PWM_TYPE    uint8_t
  #endif

  //spindle speed value, pwm value
  extern SPINDLE_PWM_TYPE spindle_speed;
#endif

#ifdef DELAY_OFF_SPINDLE
  /*M5停止激光命令*/
  extern uint8_t stop_spindle_pwm_flag;
  /* 主轴/激光 是否关闭的标识 */
  extern uint8_t stop_spindle_disable_flag;
  /*关电源计时*/
  extern uint32_t stop_spindle_timer;
  /*统计平均PWM值*/
  extern uint32_t stop_spindle_avg_pwm;
  /* 主轴/激光 是否挂起的标识 */
  extern uint8_t spindle_suspend_flag;
#endif

// Initializes spindle pins and hardware PWM, if enabled.
void spindle_init();

// Returns current spindle output state. Overrides may alter it from programmed states.
uint8_t spindle_get_state();

// Called by g-code parser when setting spindle state and requires a buffer sync.
// Immediately sets spindle running state with direction and spindle rpm via PWM, if enabled.
// Called by spindle_sync() after sync and parking motion/spindle stop override during restore.
#ifdef VARIABLE_SPINDLE

  // Called by g-code parser when setting spindle state and requires a buffer sync.
  void spindle_sync(uint8_t state, float rpm);

  // Sets spindle running state with direction, enable, and spindle PWM.
  void spindle_set_state(uint8_t state, float rpm); 
  
  // Sets spindle PWM quickly for stepper ISR. Also called by spindle_set_state().
  // NOTE: 328p PWM register is 8-bit.
  void spindle_set_speed(SPINDLE_PWM_TYPE pwm_value);
  
  // Computes 328p-specific PWM register value for the given RPM for quick updating.
  SPINDLE_PWM_TYPE  spindle_compute_pwm_value(float rpm);
  
  // get spindle speed
  inline SPINDLE_PWM_TYPE spindle_get_speed()
  {
    return spindle_speed;
  }

#else
  
  // Called by g-code parser when setting spindle state and requires a buffer sync.
  #define spindle_sync(state, rpm) _spindle_sync(state)
  void _spindle_sync(uint8_t state);

  // Sets spindle running state with direction and enable.
  #define spindle_set_state(state, rpm) _spindle_set_state(state)
  void _spindle_set_state(uint8_t state);

#endif

// Stop and start spindle routines. Called by all spindle routines and stepper ISR.
void spindle_stop();

//激光是否开启
uint8_t isLaserOpen();

#ifdef DELAY_OFF_SPINDLE

  /**
   * @brief spindle_suspend_flag_set 设置挂起状态，用于挂起恢复是开激光使能
   * @param status
   */
  inline void spindle_suspend_flag_set(uint8_t status)
  {
  	spindle_suspend_flag = status;
  }

  /**
   * @brief is_spindle_suspend_flag_set 读取挂起状态
   * @return
   */
  inline uint8_t is_spindle_suspend_flag_set(void)
  {
  	return spindle_suspend_flag;
  }

  /**
   * @brief grbl 层面关激光供电
   * @param status
   */
  void stop_spindle_disable_flag_set(uint8_t status);

  /**
   * @brief 设置延时关激光器供电，主要是为了延迟风扇关闭的时间
   * @param pwm
   */
  void delay_stop_spindle_set(uint16_t pwm);

  /**
   * @brief delay_stop_spindle
   * @return 1: 允许关激光 0：需要延时关激光
   */
  uint8_t delay_stop_spindle(void);

#endif

#endif
