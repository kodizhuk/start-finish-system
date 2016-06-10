

	/*перевірка дозволу для старту наступного лижника*/
	bool controlStartPermissionSkier(void);
	
	/*вкл індикацію дозволу старту лижника*/
	void indicationStartAllowed(void);
	
	/*відображення дозволу старту лижника на дисплеї*/
	void displayIndicationStartAllowed(void);
	
	/*записати реальний час старту лижника */
	int writeRealTimeStartSkier(uint16_t numberSkier);
	
	/*синзронізація даних про лижники із фінішом*/
	bool syncDataWithFinish(struct SKIERRESULT *skierTime);
	
	/*зчитати команди із панелі управління/смартфона*/
	int readCommandcontrolPanel(void);	
int main(void)
{
}