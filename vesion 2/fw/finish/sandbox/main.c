
int main(void)
{
	/*перевірка дозволу для старту наступного лижника*/
	bool controlStartPermissionSkier(void);
	
	/*вкл індикацію успішного зєднання зі стартом*/
	void indicationSuccessConnection(void);
	
	/*записати реальний час фінішу лижника*/
	int writeRealTimeFinishSkier(uint16_t numberSkier);
	
	/*синзронізація даних про лижники із стартом*/
	bool syncDataWithStart(struct SKIERRESULT *skierTime);
	
	/*зчитати команди із панелі управління/смартфона*/
	int readCommandcontrolPanel(void);
	
}